#ifndef CAMERARREADER_H
#define CAMERARREADER_H

#include <FrameProvider.h>

#include "opencv2/opencv.hpp"

class StreamReader;

class CameraReader : public FrameProvider
{
    Q_OBJECT

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QVariant device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool isFile READ isFile WRITE setIsFile NOTIFY isFileChanged)
    Q_PROPERTY(QRect crop READ crop WRITE setCrop NOTIFY cropChanged)
public:
    explicit CameraReader(QQuickItem *parent = nullptr);
    ~CameraReader();

    enum readerState {STOPED, STARTED, PAUSED};

    enum VideoCaptureAPIs {
           CAP_ANY          = cv::VideoCaptureAPIs::CAP_ANY         ,
           CAP_VFW          = cv::VideoCaptureAPIs::CAP_VFW         ,
           CAP_V4L          = cv::VideoCaptureAPIs::CAP_V4L         ,
           CAP_V4L2         = cv::VideoCaptureAPIs::CAP_V4L2        ,
           CAP_FIREWIRE     = cv::VideoCaptureAPIs::CAP_FIREWIRE    ,
           CAP_FIREWARE     = cv::VideoCaptureAPIs::CAP_FIREWARE    ,
           CAP_IEEE1394     = cv::VideoCaptureAPIs::CAP_IEEE1394    ,
           CAP_DC1394       = cv::VideoCaptureAPIs::CAP_DC1394      ,
           CAP_CMU1394      = cv::VideoCaptureAPIs::CAP_CMU1394     ,
           CAP_QT           = cv::VideoCaptureAPIs::CAP_QT          ,
           CAP_UNICAP       = cv::VideoCaptureAPIs::CAP_UNICAP      ,
           CAP_DSHOW        = cv::VideoCaptureAPIs::CAP_DSHOW       ,
           CAP_PVAPI        = cv::VideoCaptureAPIs::CAP_PVAPI       ,
           CAP_OPENNI       = cv::VideoCaptureAPIs::CAP_OPENNI      ,
           CAP_OPENNI_ASUS  = cv::VideoCaptureAPIs::CAP_OPENNI_ASUS ,
           CAP_ANDROID      = cv::VideoCaptureAPIs::CAP_ANDROID     ,
           CAP_XIAPI        = cv::VideoCaptureAPIs::CAP_XIAPI       ,
           CAP_AVFOUNDATION = cv::VideoCaptureAPIs::CAP_AVFOUNDATION,
           CAP_GIGANETIX    = cv::VideoCaptureAPIs::CAP_GIGANETIX   ,
           CAP_MSMF         = cv::VideoCaptureAPIs::CAP_MSMF        ,
           CAP_WINRT        = cv::VideoCaptureAPIs::CAP_WINRT       ,
           CAP_INTELPERC    = cv::VideoCaptureAPIs::CAP_INTELPERC   ,
           CAP_OPENNI2      = cv::VideoCaptureAPIs::CAP_OPENNI2     ,
           CAP_OPENNI2_ASUS = cv::VideoCaptureAPIs::CAP_OPENNI2_ASUS,
           CAP_GPHOTO2      = cv::VideoCaptureAPIs::CAP_GPHOTO2     ,
           CAP_GSTREAMER    = cv::VideoCaptureAPIs::CAP_GSTREAMER   ,
           CAP_FFMPEG       = cv::VideoCaptureAPIs::CAP_FFMPEG      ,
           CAP_IMAGES       = cv::VideoCaptureAPIs::CAP_IMAGES      ,
           CAP_ARAVIS       = cv::VideoCaptureAPIs::CAP_ARAVIS      ,
           CAP_OPENCV_MJPEG = cv::VideoCaptureAPIs::CAP_OPENCV_MJPEG,
           CAP_INTEL_MFX    = cv::VideoCaptureAPIs::CAP_INTEL_MFX
         };
    Q_ENUMS(VideoCaptureAPIs)

    QVariant source() override;
    QVariant device();
    bool isFile();
    QRect crop();

    void setSource(QVariant source) override;
    void setDevice(QVariant device);
    void setIsFile(bool isFile);
    void setCrop(QRect crop);

signals:

    void sourceChanged();
    void deviceChanged();
    void isFileChanged(bool isFile);
    void cropChanged(QRect crop);

    void stoped();
    void paused();
    void started();

    // private signals
    void startRequest();
    void pauseRequest();
    void stopRequest();
    void sendNextFrameRequest();
    void setSourceRequest(QString source);
    void setDeviceRequest(int deviceNum);
    void setIsFileRequest(bool isFile);
    void setCropRequest(QRect crop);

public slots:
    void start();
    void pause();
    void stop();
    void sendNextFrame() override;

    void startSignal();
    void pauseSignal();
    void stopSignal();
    void newFrameSignal(cv::UMat frame);
    void sourceChangedSignal(QString source);
    void deviceChangedSignal(int deviceNum);
    void isFileChangedSignal(bool isFile);
    void cropChangedSignal(QRect crop);


private slots:

private:
    QThread* p_readerThread;
    StreamReader* p_reader;
};

class StreamReader : public QObject
{
    Q_OBJECT
public:
    explicit StreamReader(QObject* parent = NULL);

    QString source();
    int device();
    bool isFile();
    QRect crop();
    ~StreamReader();

signals:
    void started();
    void paused();
    void stoped();
    void newFrame(cv::UMat frame);
    void sourceChanged(QString source);
    void deviceChanged(int device);
    void isFileChanged(bool isFile);
    void cropChanged(QRect crop);

public slots:
    void start();
    void pause();
    void stop();
    void setSource(QString source);
    void setDevice(int device);
    void setIsFile(bool isFile);
    void setCrop(QRect crop);
    void sendNextFrame();

private:
    CameraReader::readerState m_state;
    bool m_isFile;
    QString m_sourceString;
    int m_deviceNum;
    QRect m_crop;

    cv::UMat m_backbuffer;
    cv::UMat m_frontbuffer;
    cv::VideoCapture m_device;
};
#endif // CAMERARREADER_H
