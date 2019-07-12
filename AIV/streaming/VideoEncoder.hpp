#pragma once

#include <QObject>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/hwcontext.h>
//#include <libavutil/hwcontext_qsv.h>
#include <libavutil/md5.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavutil/log.h>
}
#include "opencv2/opencv.hpp"

#include <QMap>
#include <QString>

#include <QMutex>

#include "live555.h"

class VideoEncoder : public QObject, public FramedSource
{
    Q_OBJECT
public:
    explicit VideoEncoder(UsageEnvironment* env, QObject* parent = nullptr);
    ~VideoEncoder() override;

protected:
    void doGetNextFrame() override;

public slots:
    void newFrame(cv::UMat frame);

signals:
    void opened();

private:
    bool m_inited;
    void init();

    int m_width;
    int m_height;

    QString m_encoder;

    cv::UMat m_cvFrame;

    AVFrame* p_frame;
    AVPacket* p_packet;
    int64_t pkg_pts;

    AVCodec* p_outputCodec;
    AVCodecContext* p_outputCodecContext;

    SwsContext* p_scaleContext;

    QMutex m_streamMutex;

    QMap<QString, QString> m_encoderOptions;

    UsageEnvironment* p_env;
    EventTriggerId m_newFrameEvent;
    static void deliverFrame0(void* clientData);
    void encodeFrame();
    void deliverFrame();

    //virtual Boolean isRTPSource() const;
    //virtual Boolean isH264VideoStreamFramer() const;
};
