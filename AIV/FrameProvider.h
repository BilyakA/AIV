#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QQuickItem>

#include "opencv2/opencv.hpp"

class FrameProvider : public QQuickItem
{
    Q_OBJECT

public:
    explicit FrameProvider(QQuickItem *parent = Q_NULLPTR);

signals:
    void newFrame(cv::UMat frame);

public slots:
    virtual void sendNextFrame() = 0;
};

#endif // FRAMEPROVIDER_H
