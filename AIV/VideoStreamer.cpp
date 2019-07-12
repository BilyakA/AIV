#include "VideoStreamer.hpp"

#include <QDebug>
#include <QThread>

#include "streaming/VideoEncoder.hpp"

#include <QMetaObject>

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>
#include <GroupsockHelper.hh>

VideoStreamer::VideoStreamer(QQuickItem* parent)
    : QObject(parent)
    , QQmlParserStatus()
    , p_sourceItem(nullptr)
{

}

QObject* VideoStreamer::source()
{
    return p_sourceItem;
}
void VideoStreamer::setSource(QObject *source)
{
    if (p_sourceItem == source) {
        return;
    }
    p_sourceItem = source;

    connect(p_sourceItem, SIGNAL(newFrame(frameData)),
            this, SLOT(updateFrame(frameData)));

    emit sourceChanged();
}

void VideoStreamer::updateFrame(frameData frame)
{
    //qDebug() << "new frame!";

    VideoEncoder* encoder = qobject_cast<VideoEncoder*>(p_encoder);
    if (!encoder) {
        return;
    }

    QMetaObject::invokeMethod(p_encoder, [encoder, frame](){
        encoder->newFrame(frame.frame);
    }, Qt::QueuedConnection);
}

void VideoStreamer::classBegin()
{

}
void VideoStreamer::componentComplete()
{
    p_scheduler = BasicTaskScheduler::createNew();
    p_env = BasicUsageEnvironment::createNew(*p_scheduler);

    m_destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*p_env);

    m_rtpPortNum = 18888;
    m_rtcpPortNum = m_rtpPortNum+1;
    m_ttl = 255;

    p_rtpPort = new Port(m_rtpPortNum);
    p_rtcpPort = new Port(m_rtcpPortNum);

    p_rtpGroupsock = new Groupsock(*p_env, m_destinationAddress, *p_rtpPort, m_ttl);
    p_rtpGroupsock->multicastSendOnly(); // we're a SSM source
    p_rtcpGroupsock = new Groupsock(*p_env, m_destinationAddress, *p_rtcpPort, m_ttl);
    p_rtcpGroupsock->multicastSendOnly(); // we're a SSM source

    OutPacketBuffer::maxSize = 100000;
    p_videoSink = H264VideoRTPSink::createNew(*p_env, p_rtpGroupsock, 96);

    m_estimatedSessionBandwidth = 500; // in kbps; for RTCP b/w share
    m_maxCNAMElen = 100;
    unsigned char CNAME[m_maxCNAMElen+1];
    gethostname((char*)CNAME, m_maxCNAMElen);
    CNAME[m_maxCNAMElen] = '\0'; // just in case
    p_rtcp = RTCPInstance::createNew(*p_env, p_rtcpGroupsock,
                              m_estimatedSessionBandwidth, CNAME,
                              p_videoSink, NULL /* we're a server */,
                              True /* we're a SSM source */);

    p_rtspServer = RTSPServer::createNew(*p_env, 8554);
    if (p_rtspServer == NULL) {
        qDebug() << "Failed to create RTSP server: " << p_env->getResultMsg();
      exit(1);
    }
    p_sms = ServerMediaSession::createNew(*p_env, "testStream", "testStreamInfo",
                     "Session streamed by \"testH264VideoStreamer\"",
                                             True /*SSM*/);
    p_sms->addSubsession(PassiveServerMediaSubsession::createNew(*p_videoSink, p_rtcp));
    p_rtspServer->addServerMediaSession(p_sms);

    char* url = p_rtspServer->rtspURL(p_sms);
    qDebug() << "Created stream \"" << url << "\"";
    delete[] url;

    p_encoder = new VideoEncoder(p_env, nullptr);
    p_encoderThread = new QThread(this);
    p_encoderThread->setObjectName("encoder thread");
    p_encoder->moveToThread(p_encoderThread);
    p_encoderThread->start();

    // Create a framer for the Video Elementary Stream:
    p_videoSource = H264VideoStreamFramer::createNew(*p_env, p_encoder);

    connect(p_encoder, &VideoEncoder::opened, [this](){
        p_videoSink->startPlaying(*p_videoSource, nullptr, nullptr);
    });

    p_streamer = new LiveStreamer(p_env, nullptr);
    p_streamerThread = new QThread(this);
    p_streamerThread->setObjectName("streamer thread");
    p_streamer->moveToThread(p_streamerThread);
    connect(p_streamerThread, &QThread::started, p_streamer, &LiveStreamer::startStream);
    p_streamerThread->start();
}
