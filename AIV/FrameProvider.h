#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QQuickItem>

#include "opencv2/opencv.hpp"

typedef struct frameData {
    /// frame in BGR
    cv::UMat frame;

    /// frame in grayscale
    cv::UMat frameGrayscale;

    /// detected features
    std::vector <cv::Point2f> features;

    /// current displating frame
    cv::UMat displayFrame;

    /// displaying overlay in BGRA
    cv::UMat overlay;

    /// global affine matrix
    cv::Mat homographyTransform;
} frameData;

class FrameProvider : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit FrameProvider(QQuickItem *parent = Q_NULLPTR);

    virtual QVariant source() = 0;

signals:
    void sourceChanged();

    void newFrame(frameData frame);

public slots:
    virtual void setSource(QVariant source) = 0;

    virtual void sendNextFrame() = 0;
};

#endif // FRAMEPROVIDER_H
