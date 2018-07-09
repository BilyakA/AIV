#include "CameraRreader.h"
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

StreamReader::StreamReader(QObject* parent)
    : QObject(parent)
    , m_state(CameraReader::STOPED)
    , m_isFile(false)
    , m_sourceString("")
    , m_crop(0, 0, 0, 0)
{

}

QString StreamReader::source()
{
    return m_sourceString;
}
bool StreamReader::isFile()
{
    return m_isFile;
}
QRect StreamReader::crop()
{
    return m_crop;
}

StreamReader::~StreamReader()
{
    stop();
}

void StreamReader::start()
{
    if (m_state == CameraReader::STOPED) {
        return;
    }
    if (m_state == CameraReader::PAUSED) {
        m_state = CameraReader::STARTED;
        emit started();
    }
    if (!m_isFile) {
        while (m_state == CameraReader::STARTED) {
            if (m_device.grab()) {
                QThread::msleep(0);
                QCoreApplication::processEvents();
            }
        }
    }
}
void StreamReader::pause()
{
    m_state = CameraReader::PAUSED;
    emit paused();
}
void StreamReader::stop()
{
    m_state = CameraReader::STOPED;
    if (m_device.isOpened()) {
        m_device.release();
    }
    emit stoped();
}
void StreamReader::setSource(QString source)
{
    if (m_sourceString == source) {
        return;
    }

    if (m_state != CameraReader::STOPED) {
        stop();
    }
    setIsFile(false);
    m_sourceString = source;
    m_device.set(cv::CAP_PROP_BUFFERSIZE, 4);
    if (m_device.open( m_sourceString.toStdString() )) {
        pause();
        return;
    } else {
        qCritical() << "Can not open" << m_sourceString;
        return;
    }

    emit sourceChanged(m_sourceString);
}
void StreamReader::setIsFile(bool isFile)
{
    if (m_isFile != isFile) {
        m_isFile = isFile;
        emit isFileChanged(m_isFile);
    }
}
void StreamReader::setCrop(QRect crop)
{
    if (m_crop == crop) {
        return;
    }
    m_crop = crop;
    emit cropChanged(m_crop);
}
void StreamReader::sendNextFrame()
{
    if (m_isFile) {
        if (m_device.read(m_frontbuffer)) {
            if (m_crop.width() > 0 && m_crop.height() > 0) {
                emit newFrame(m_frontbuffer(cv::Rect(m_crop.x(), m_crop.y(), m_crop.width(), m_crop.height())));
            } else {
                emit newFrame(m_frontbuffer);
            }
        }
    } else {
        m_device.retrieve(m_backbuffer);
        m_backbuffer.copyTo(m_frontbuffer);
        if (m_crop.width() > 0 && m_crop.height() > 0) {
            emit newFrame(m_frontbuffer(cv::Rect(m_crop.x(), m_crop.y(), m_crop.width(), m_crop.height())));
        } else {
            emit newFrame(m_frontbuffer);
        }
    }
}

CameraReader::CameraReader(QQuickItem *parent)
    : FrameProvider(parent)
    , p_readerThread(NULL)
    , p_reader(NULL)
{
    p_reader = new StreamReader();
    p_readerThread = new QThread(this);
    p_readerThread->setObjectName("readerThread");

    p_reader->moveToThread(p_readerThread);

    connect(this, &CameraReader::startRequest, p_reader, &StreamReader::start, Qt::QueuedConnection);
    connect(this, &CameraReader::pauseRequest, p_reader, &StreamReader::pause, Qt::QueuedConnection);
    connect(this, &CameraReader::stopRequest, p_reader, &StreamReader::stop, Qt::QueuedConnection);
    connect(this, &CameraReader::setSourceRequest, p_reader, &StreamReader::setSource, Qt::QueuedConnection);
    connect(this, &CameraReader::setIsFileRequest, p_reader, &StreamReader::setIsFile, Qt::QueuedConnection);
    connect(this, &CameraReader::setCropRequest, p_reader, &StreamReader::setCrop, Qt::QueuedConnection);
    connect(this, &CameraReader::sendNextFrameRequest, p_reader, &StreamReader::sendNextFrame, Qt::QueuedConnection);

    connect(p_reader, &StreamReader::started, this, &CameraReader::startSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::paused, this, &CameraReader::pauseSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::stoped, this, &CameraReader::stopSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::newFrame, this, &CameraReader::newFrameSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::sourceChanged, this, &CameraReader::sourceChangedSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::isFileChanged, this, &CameraReader::isFileChangedSignal, Qt::QueuedConnection);
    connect(p_reader, &StreamReader::cropChanged, this, &CameraReader::cropChangedSignal, Qt::QueuedConnection);

    p_readerThread->start();
}

QVariant CameraReader::source()
{
    return QVariant(p_reader->source());
}
bool CameraReader::isFile()
{
    return p_reader->isFile();
}
QRect CameraReader::crop()
{
    return p_reader->crop();
}

void CameraReader::setSource(QVariant src)
{
    QString str = src.toString();
    if (str.isEmpty()) {
        qWarning() << "empty source srting for CameraReader";
        return;
    }
    emit setSourceRequest(str);
}
void CameraReader::setIsFile(bool isFile)
{
    emit setIsFileRequest(isFile);
}
void CameraReader::setCrop(QRect crop)
{
    emit setCropRequest(crop);
}

void CameraReader::start()
{
    emit startRequest();
}
void CameraReader::pause()
{
    emit pauseRequest();
}
void CameraReader::stop()
{
    emit stopRequest();
}
void CameraReader::sendNextFrame()
{
    emit sendNextFrameRequest();
}

void CameraReader::startSignal()
{
    emit started();
}
void CameraReader::pauseSignal()
{
    emit paused();
}
void CameraReader::stopSignal()
{
    emit stoped();
}
void CameraReader::newFrameSignal(cv::UMat frame)
{
    frameData data;
    data.frame = frame;
    emit newFrame(data);
}
void CameraReader::sourceChangedSignal(QString source)
{
    emit sourceChanged();
}
void CameraReader::isFileChangedSignal(bool isFile)
{
    emit isFileChanged(isFile);
}
void CameraReader::cropChangedSignal(QRect crop)
{
    emit cropChanged(crop);
}

CameraReader::~CameraReader()
{
    if (p_reader) {
        p_reader->deleteLater();
    }
    if (p_readerThread) {
        p_readerThread->deleteLater();
    }
}

