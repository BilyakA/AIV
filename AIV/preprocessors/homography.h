#ifndef HOMOGRAPHY_H
#define HOMOGRAPHY_H

#include <QObject>
#include "../VideoPreprocessor.h"
#include <opencv2/opencv.hpp>

class PreprocessorHomography : public internalFramePreprocessor
{
public:
    PreprocessorHomography();

public:
    void processFrame(frameData* metaData) override;
private:
    frameData prevData;
    std::vector <cv::Point2f> prev_corner, cur_corner;
    std::vector <uchar> status;
    std::vector <float> err;
};

#endif // HOMOGRAPHY_H
