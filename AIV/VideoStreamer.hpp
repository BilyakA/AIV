#pragma once

#include <QObject>
#include <QQmlParserStatus>
#include "FrameProvider.h"

#include "streaming/live555.h"

#include "streaming/VideoEncoder.hpp"
#include "streaming/LiveStreamer.hpp"

class VideoStreamer : public QObject, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QObject* source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit VideoStreamer(QQuickItem *parent = nullptr);

    QObject* source();

public slots:
    void setSource(QObject* source);

private slots:
    void updateFrame(frameData frame);

protected:
    void classBegin() override;
    void componentComplete() override;

signals:
    void sourceChanged();

private:
    QObject* p_sourceItem;

    VideoEncoder* p_encoder;
    LiveStreamer* p_streamer;

    QThread* p_streamerThread;
    QThread* p_encoderThread;

    TaskScheduler* p_scheduler;
    UsageEnvironment* p_env;

    struct in_addr m_destinationAddress;

    unsigned short m_rtpPortNum;
    unsigned short m_rtcpPortNum;
    unsigned char m_ttl;

    Port* p_rtpPort;
    Port* p_rtcpPort;

    Groupsock* p_rtpGroupsock;
    Groupsock* p_rtcpGroupsock;

    H264VideoRTPSink* p_videoSink;
    H264VideoStreamFramer* p_videoSource;

    unsigned m_estimatedSessionBandwidth;
    unsigned m_maxCNAMElen;

    RTCPInstance* p_rtcp;
    RTSPServer* p_rtspServer;
    ServerMediaSession* p_sms;
};
