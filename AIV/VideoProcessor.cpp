#include "VideoProcessor.h"
#include "processors/peopledetect.h"

VideoProcessor::VideoProcessor(QQuickItem *parent)
    : FrameProvider(parent)
    , p_sourceItem(NULL)
    , m_type(INVALID)
    , p_processor(NULL)
{

}

VideoProcessor::ProcessorType VideoProcessor::type()
{
    return m_type;
}
void VideoProcessor::setType(VideoProcessor::ProcessorType type)
{
    if (p_processor) {
        qWarning() << "runtime changes of filter type are forbidden";
        return;
    }
    if (m_type == type) {
        return;
    }
    m_type = type;
    switch(m_type) {
    case PEOPLEDETECT:
        p_processor = new ProcessorPeopleDetect();
        break;
    case INVALID:
    default:
        break;
    }
    emit typeChanged();
}
QVariant VideoProcessor::source()
{
    return QVariant::fromValue(p_sourceItem);
}
void VideoProcessor::setSource(QVariant source)
{
    if (!source.canConvert<QQuickItem*>()) {
        qWarning() << "invalid source for VideoProcessor";
    }
    QQuickItem* p_source = qvariant_cast<QQuickItem*>(source);

    if (p_sourceItem == p_source) {
        return;
    }

    FrameProvider* provider = qobject_cast<FrameProvider*>(p_source);
    if (!provider) {
        return;
    }

    if (p_sourceItem) {
        disconnect(p_sourceItem, 0, this, 0);
    }

    p_sourceItem = provider;
    connect(provider, &FrameProvider::newFrame, this, &VideoProcessor::processFrame, Qt::DirectConnection);
    connect(this, &VideoProcessor::requestFrame, provider, &FrameProvider::sendNextFrame, Qt::QueuedConnection);
    emit sourceChanged();
}

void VideoProcessor::sendNextFrame()
{
    emit requestFrame();
}

void VideoProcessor::processFrame(frameData metaData)
{
    if (p_processor) {
        p_processor->processFrame(&metaData);
    }
    emit newFrame(metaData);
}
