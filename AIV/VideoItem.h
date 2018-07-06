#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QObject>
#include <QQuickItem>
#include <QImage>

#include "opencv2/opencv.hpp"
#include "FrameProvider.h"

class VideoItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QQuickItem* source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit VideoItem(QQuickItem *parent = nullptr);

    QQuickItem* source();

signals:
    void sourceChanged();

public slots:
    void setSource(QQuickItem* source);

    void updateFrame(frameData frame);

private:
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *data) override;
    QImage currentImg;

    QQuickItem* p_sourceItem;
};

#endif // VIDEOITEM_H
