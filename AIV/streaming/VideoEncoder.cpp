#include "VideoEncoder.hpp"

#include <QDebug>
#include <QString>

static inline QString ffmpegErrorStr(int errNo)
{
    char buffer[1024];
    return QString(av_make_error_string(buffer, 1024, errNo));
}

VideoEncoder::VideoEncoder(UsageEnvironment* env, QObject *parent)
    : QObject(parent)
    , FramedSource(*env)
    , m_inited(false)
    , m_width(0)
    , m_height(0)
    , m_encoder("h264_qsv")
    , p_frame(nullptr)
    , p_packet(nullptr)
    , pkg_pts(0)
    , p_outputCodec(nullptr)
    , p_outputCodecContext(nullptr)
    , p_scaleContext(nullptr)
    , p_env(env)
{
    //av_log_set_level(AV_LOG_DEBUG);

    m_encoderOptions.insert("bitrate", QString::number(800000));
    m_encoderOptions.insert("preset", "fast");
    m_encoderOptions.insert("fps", QString::number(25));

    p_packet = av_packet_alloc();
    av_init_packet(p_packet);

    p_frame = av_frame_alloc();

    m_newFrameEvent = p_env->taskScheduler().createEventTrigger(deliverFrame0);
}

VideoEncoder::~VideoEncoder()
{

}

void VideoEncoder::init()
{
    qDebug() << "Opening " << m_encoder << " codec";
    int ret = 0;
    bool ok = false;

    p_outputCodec = avcodec_find_encoder_by_name(m_encoder.toStdString().c_str());
    if (!p_outputCodec) {
        qWarning() << "Could not find encoder " << m_encoder;
        return;
    }
    p_outputCodecContext = avcodec_alloc_context3(p_outputCodec);
    if (!p_outputCodecContext) {
        qWarning() << "Could not create encoding context";
        return;
    }

    p_outputCodecContext->bit_rate = m_encoderOptions.take("bitrate").toInt(&ok);
    if (!ok) {
        qWarning() << "Can't convert bitrate!";
    }
    p_outputCodecContext->rc_max_rate = p_outputCodecContext->bit_rate;
    p_outputCodecContext->width = m_width;
    p_outputCodecContext->height = m_height;
    p_outputCodecContext->time_base.num = 1;
    p_outputCodecContext->time_base.den = m_encoderOptions.take("fps").toInt(&ok);
    if (!ok) {
        qWarning() << "Can't convert fps!";
    }
    p_outputCodecContext->gop_size = p_outputCodecContext->time_base.den;     // make sure we won't lose more than 1 sec of video
    p_outputCodecContext->keyint_min = p_outputCodecContext->time_base.den;
    p_outputCodecContext->max_b_frames = 0;

    // TODO: ffmpeg codec should contain pix format?
    if (m_encoder == "h264_qsv" || m_encoder == "h264_amf") {
        p_outputCodecContext->pix_fmt = AV_PIX_FMT_NV12;
    } else {
        p_outputCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    }

    AVDictionary* codecOptionsDict = NULL;
    foreach (QString key, m_encoderOptions.keys()) {
        qDebug() << "   Option " << key << " = " << m_encoderOptions[key];
        av_dict_set(&codecOptionsDict, key.toStdString().c_str(), m_encoderOptions[key].toStdString().c_str(), 0 );
    }

    ret = avcodec_open2(p_outputCodecContext, p_outputCodec, &codecOptionsDict);
    if (ret < 0) {
        qWarning() << "Could not open output codec:" << ffmpegErrorStr(ret);
        return;
    }

    av_dict_free(&codecOptionsDict);

    p_scaleContext = sws_getContext(m_width, m_height, AV_PIX_FMT_BGR24,
           m_width, m_height,(AVPixelFormat)p_outputCodecContext->pix_fmt,
           SWS_FAST_BILINEAR, NULL, NULL, NULL);
    if (!p_scaleContext) {
       qWarning() << "Could not create scale";
       return;
    }

    p_frame->format = p_outputCodecContext->pix_fmt;
    p_frame->width = p_outputCodecContext->width;
    p_frame->height = p_outputCodecContext->height;

    ret = av_image_alloc(p_frame->data, p_frame->linesize, p_frame->width, p_frame->height, (AVPixelFormat)p_frame->format, 32);
    if (ret < 0) {
        qWarning() << "Could not allocate recorder picture buffer:" << ffmpegErrorStr(ret);
        return;
    }

    m_inited = true;
}

void VideoEncoder::newFrame(cv::UMat image)
{
    if (!m_inited) {
        m_width = image.cols;
        m_height = image.rows;

        init();

        emit opened();
    }

    m_streamMutex.lock();

    m_cvFrame = image.clone();

    m_streamMutex.unlock();

    p_env->taskScheduler().triggerEvent(m_newFrameEvent, this);
}

void VideoEncoder::encodeFrame()
{
    int ret = 0;

    if (!m_inited) {
        return;
    }

    m_streamMutex.lock();

    // convert OpenCV's RGB image to ffmpeg's YUV420
    cv::Mat _image = m_cvFrame.getMat(cv::ACCESS_READ);
    const int stride[] = { static_cast<int>(_image.step[0]) };
    sws_scale(p_scaleContext, &(_image.data), stride, 0, _image.rows, p_frame->data, p_frame->linesize);
    _image.release();

    m_streamMutex.unlock();

    ret = avcodec_send_frame(p_outputCodecContext, p_frame);
    if (ret < 0) {
        qCritical() << "Error sending frame to codec:" << ffmpegErrorStr(ret);
        return;
    }

    av_packet_unref(p_packet);
    ret = avcodec_receive_packet(p_outputCodecContext, p_packet);
    if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF && ret != -11) {
        qCritical() << "Error getting packet from codec:" << ffmpegErrorStr(ret);
        //m_streamMutex.unlock();
        //return;
    }

    if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF && ret != -11) {
        p_packet->pts = pkg_pts;
        p_packet->dts = pkg_pts;
        p_packet->duration = 1;

        //qDebug() << "Packet size=" << p_packet->size << "dts=" << p_packet->dts << "pts=" << p_packet->pts;

        pkg_pts++;
    }
}

void VideoEncoder::deliverFrame0(void* clientData)
{
    static_cast<VideoEncoder*>(clientData)->deliverFrame();
}

void VideoEncoder::deliverFrame()
{
    if (!isCurrentlyAwaitingData()) return; // we're not ready for the data yet

    encodeFrame();

    u_int8_t* newFrameDataStart = p_packet->data;
    unsigned newFrameSize = static_cast<unsigned int>(p_packet->size);

    // Deliver the data here:
    if (newFrameSize > fMaxSize) {
      fFrameSize = fMaxSize;
      fNumTruncatedBytes = newFrameSize - fMaxSize;
    } else {
      fFrameSize = newFrameSize;
    }
    gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.

    memmove(fTo, newFrameDataStart, fFrameSize);

    // After delivering the data, inform the reader that it is now available:
    FramedSource::afterGetting(this);
}

void VideoEncoder::doGetNextFrame()
{
    deliverFrame();
}
