#pragma once

#include <QObject>
#include "../VideoProcessor.h"
#include <opencv2/opencv.hpp>

class ProcessorPeopleDetect : public internalFrameProcessor
{
public:
    ProcessorPeopleDetect();

public:
    void processFrame(frameData* metaData) override;

private:
    void adjustRect(cv::Rect & r) const;
    cv::HOGDescriptor hog;
};
