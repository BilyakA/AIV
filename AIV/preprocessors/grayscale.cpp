#include "grayscale.h"

PreprocessorGrayscale::PreprocessorGrayscale()
{

}

void PreprocessorGrayscale::processFrame(frameData* metaData)
{
    if (metaData->frame.empty()) {
        qWarning() << "Empty frame as input to grayscale filter";
        return;
    }
    cv::cvtColor(metaData->frame, metaData->frameGrayscale, cv::COLOR_BGR2GRAY);
    return;
}
