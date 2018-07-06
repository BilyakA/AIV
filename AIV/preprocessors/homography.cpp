#include "homography.h"

PreprocessorHomography::PreprocessorHomography()
{

}

void PreprocessorHomography::processFrame(frameData*  metaData)
{
    size_t count;
    float median_error;
    bool match_found;

    prev_corner.clear();
    cur_corner.clear();
    prevData.features.clear();
    metaData->features.clear();
    status.clear();
    err.clear();

    if (metaData->frame.empty()) {
        qWarning() << "Empty frame as input to homography filter";
        return;
    }
    if (metaData->frameGrayscale.empty()) {
        qWarning() << "Empty grayscale frame as input to homography filter";
        return;
    }

    if (prevData.frame.empty()) {
        prevData.frame = metaData->frame;
        prevData.overlay = metaData->overlay;
        prevData.frameGrayscale = metaData->frameGrayscale;
    }

    cv::goodFeaturesToTrack(prevData.frameGrayscale, prev_corner, 300, 0.10, 20);

    if (!prev_corner.size()) {
        prevData.frame = metaData->frame;
        prevData.overlay = metaData->overlay;
        prevData.frameGrayscale = metaData->frameGrayscale;

        qDebug() << "no features found, skipping!";
        return;
    }

    cv::calcOpticalFlowPyrLK(prevData.frameGrayscale, metaData->frameGrayscale, prev_corner, cur_corner, status, err );

    median_error = 0;
    count = 0;

    // calculate medium error
    for(size_t i=0; i < status.size(); i++) {
        if(status[i]) {
            float delta = err[i] - median_error;
            median_error += delta / ++count;
        }
    }

    match_found = false;
    // weed out bad matches
    for(size_t i=0; i < status.size(); i++) {
        if(status[i]) {
            if (err[i] < median_error) {
                prevData.features.push_back(prev_corner[i]);
                metaData->features.push_back(cur_corner[i]);
                match_found = true;
            }
        }
    }

    if (!match_found) {
        prevData.frame = metaData->frame;
        prevData.overlay = metaData->overlay;
        prevData.frameGrayscale = metaData->frameGrayscale;

        qDebug() << "no strong features found, skipping!";
        return;
    }

    metaData->homographyTransform = cv::findHomography(prevData.features, metaData->features, cv::RANSAC, 3);

    //for(size_t i=0; i < metaData->features.size(); i++) {
    //    cv::arrowedLine(prevData.frame, prevData.features[i], metaData->features[i], cv::Scalar(255, 0, 0, 255), 1, 8, 0, 0.2);
    //}

    cv::swap(prevData.frame, metaData->frame);
    cv::swap(prevData.overlay, metaData->overlay);
    cv::swap(prevData.frameGrayscale, metaData->frameGrayscale);

    return;
}
