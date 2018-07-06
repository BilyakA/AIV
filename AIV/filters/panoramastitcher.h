#ifndef PANORAMASTITCHER_H
#define PANORAMASTITCHER_H

#include <QObject>
#include "../VideoFilter.h"
#include <opencv2/opencv.hpp>

class PanoramaStitcher : public internalFrameFilter
{
public:
    PanoramaStitcher();

public slots:
    void processFrame(frameData* metaData);

private:
    cv::UMat panorama;
    cv::Rect2d ROI;
};

#endif // PANORAMASTITCHER_H
