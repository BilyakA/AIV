#include "VideoFilter.h"
#include "filters/panoramastitcher.h"
#include "filters/stabilizationfeatures.h"

VideoFilter::VideoFilter(QQuickItem *parent)
    : FrameProvider(parent)
    , p_sourceItem(NULL)
    , m_type(INVALID)
    , p_filter(NULL)
{

}

VideoFilter::FilterType VideoFilter::type()
{
    return m_type;
}
void VideoFilter::setType(VideoFilter::FilterType type)
{
    if (p_filter) {
        qWarning() << "runtime changes of filter type are forbidden";
        return;
    }
    if (m_type == type) {
        return;
    }
    m_type = type;
    switch(m_type) {
    case STABILIZATION:
        p_filter = new StabilizationFeatures();
        break;
    case STICHER:
        p_filter = new PanoramaStitcher();
        break;
    case INVALID:
    default:
        break;
    }
    emit typeChanged();
}
QVariant VideoFilter::source()
{
    return QVariant::fromValue(p_sourceItem);
}
void VideoFilter::setSource(QVariant source)
{
    if (!source.canConvert<QQuickItem*>()) {
        qWarning() << "invalid source for VideoFilter";
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
    connect(provider, &FrameProvider::newFrame, this, &VideoFilter::processFrame, Qt::DirectConnection);
    connect(this, &VideoFilter::requestFrame, provider, &FrameProvider::sendNextFrame, Qt::QueuedConnection);
    emit sourceChanged();
}

void VideoFilter::sendNextFrame()
{
    emit requestFrame();
}

void VideoFilter::processFrame(frameData metaData)
{
    if (p_filter) {
        p_filter->processFrame(&metaData);
    }
    emit newFrame(metaData);
}
