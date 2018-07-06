#ifndef PREPROCESSORGRAYSCALE_H
#define PREPROCESSORGRAYSCALE_H

#include <QObject>
#include "../VideoPreprocessor.h"
#include <opencv2/opencv.hpp>

class PreprocessorGrayscale : public internalFramePreprocessor
{
public:
    PreprocessorGrayscale();

public:
    void processFrame(frameData* metaData) override;
};

#endif // PREPROCESSORGRAYSCALE_H
