#include "VideoPreprocessor.h"
#include "preprocessors/grayscale.h"
#include "preprocessors/homography.h"

VideoPreprocessor::VideoPreprocessor(QQuickItem *parent)
    : FrameProvider(parent)
    , p_sourceItem(NULL)
    , m_type(INVALID)
    , p_processor(NULL)
{

}

VideoPreprocessor::PreprocessorType VideoPreprocessor::type()
{
    return m_type;
}
void VideoPreprocessor::setType(VideoPreprocessor::PreprocessorType type)
{
    if (p_processor) {
        qWarning() << "runtime changes of preprocessor type are forbidden";
        return;
    }
    if (m_type == type) {
        return;
    }
    m_type = type;
    switch(m_type) {
    case GRAYSCALE:
        p_processor = new PreprocessorGrayscale();
        break;
    case HOMOGRAPHY:
        p_processor = new PreprocessorHomography();
        break;
    case INVALID:
    default:
        break;
    }
    emit typeChanged();
}
QVariant VideoPreprocessor::source()
{
    return QVariant::fromValue(p_sourceItem);
}
void VideoPreprocessor::setSource(QVariant source)
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
    connect(provider, &FrameProvider::newFrame, this, &VideoPreprocessor::processFrame, Qt::DirectConnection);
    connect(this, &VideoPreprocessor::requestFrame, provider, &FrameProvider::sendNextFrame, Qt::QueuedConnection);
    emit sourceChanged();
}

void VideoPreprocessor::sendNextFrame()
{
    emit requestFrame();
}

void VideoPreprocessor::processFrame(frameData metaData)
{
    if (p_processor) {
        p_processor->processFrame(&metaData);
    }
    emit newFrame(metaData);
}
