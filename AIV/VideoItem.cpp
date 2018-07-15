#include "VideoItem.h"
#include <QSGImageNode>
#include <QQuickWindow>
#include <QImage>

#include "FrameProvider.h"

VideoItem::VideoItem(QQuickItem *parent)
    : QQuickItem(parent)
    , p_sourceItem(NULL)
{
    setFlag(ItemHasContents, true);
    currentImg = QImage(QSize(1, 1), QImage::Format_RGB32);
    currentImg.fill(QColor(0, 0, 0, 0));
}

QQuickItem* VideoItem::source()
{
    return p_sourceItem;
}
void VideoItem::setSource(QQuickItem *source)
{
    if (p_sourceItem == source) {
        return;
    }

    FrameProvider* provider = qobject_cast<FrameProvider*>(source);
    if (!provider) {
        return;
    }

    if (p_sourceItem) {
        disconnect(p_sourceItem, 0, this, 0);
        disconnect(window(), 0, p_sourceItem, 0);
    }

    p_sourceItem = provider;
    connect(provider, &FrameProvider::newFrame, this, &VideoItem::updateFrame, Qt::DirectConnection);
    connect(window(), &QQuickWindow::afterRendering, provider, &FrameProvider::sendNextFrame, Qt::QueuedConnection);
    emit sourceChanged();
}

void VideoItem::updateFrame(frameData data)
{
    QImage image(data.frame.cols, data.frame.rows, QImage::Format_RGB32);
    cv::Mat screenImage = cv::Mat(data.frame.rows, data.frame.cols, CV_8UC4, image.bits());

    cv::cvtColor(data.frame, screenImage, cv::COLOR_RGB2RGBA);

    currentImg = image;
    update();
}

QSGNode* VideoItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    QSGImageNode * node;
    if (!oldNode) {
        node = window()->createImageNode();
        oldNode = node;
    } else {
        node = static_cast<QSGImageNode *>(oldNode);
    }

    QSGTexture *texture = window()->createTextureFromImage(currentImg);

    node->setRect(QRectF(QPointF(0.0, 0.0), texture->textureSize()));
    node->setSourceRect(QRectF(QPointF(0.0, 0.0), texture->textureSize()));

    node->setTexture(texture);
    node->setOwnsTexture(true);

    return node;
}
