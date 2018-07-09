#ifndef CAMERARREADER_H
#define CAMERARREADER_H

#include <FrameProvider.h>

#include "opencv2/opencv.hpp"

class StreamReader;

class CameraReader : public FrameProvider
{
    Q_OBJECT

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool isFile READ isFile WRITE setIsFile NOTIFY isFileChanged)
    Q_PROPERTY(QRect crop READ crop WRITE setCrop NOTIFY cropChanged)
public:
    explicit CameraReader(QQuickItem *parent = nullptr);
    ~CameraReader();

    enum readerState {STOPED, STARTED, PAUSED};

    QVariant source() override;
    bool isFile();
    QRect crop();

    void setSource(QVariant source) override;
    void setIsFile(bool isFile);
    void setCrop(QRect crop);

signals:

    void sourceChanged();
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
    bool isFile();
    QRect crop();
    ~StreamReader();

signals:
    void started();
    void paused();
    void stoped();
    void newFrame(cv::UMat frame);
    void sourceChanged(QString source);
    void isFileChanged(bool isFile);
    void cropChanged(QRect crop);

public slots:
    void start();
    void pause();
    void stop();
    void setSource(QString source);
    void setIsFile(bool isFile);
    void setCrop(QRect crop);
    void sendNextFrame();

private:
    CameraReader::readerState m_state;
    bool m_isFile;
    QString m_sourceString;
    QRect m_crop;

    cv::UMat m_backbuffer;
    cv::UMat m_frontbuffer;
    cv::VideoCapture m_device;
};
#endif // CAMERARREADER_H
