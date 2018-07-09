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
        qWarning() << "Empty frame as input to homography filter. Skipping...";
        return;
    }
    if (metaData->frameGrayscale.empty()) {
        qWarning() << "Empty grayscale frame as input to homography filter. Skipping...";
        return;
    }

    if (prevData.frame.empty()) {
        prevData.frame = metaData->frame;
        prevData.overlay = metaData->overlay;
        prevData.frameGrayscale = metaData->frameGrayscale;
    }

    cv::goodFeaturesToTrack(prevData.frameGrayscale, prev_corner, 300, 0.10, 20);

    if (!prev_corner.size()) {
        metaData->frame.copyTo(prevData.frame);
        metaData->overlay.copyTo(prevData.overlay);
        metaData->frameGrayscale.copyTo(prevData.frameGrayscale);

        qDebug() << "no features found. Skipping...";
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
            if (err[i] <= median_error) {
                prevData.features.push_back(prev_corner[i]);
                metaData->features.push_back(cur_corner[i]);
                match_found = true;
            }
        }
    }

    if (!match_found) {
        metaData->frame.copyTo(prevData.frame);
        metaData->overlay.copyTo(prevData.overlay);
        metaData->frameGrayscale.copyTo(prevData.frameGrayscale);

        qDebug() << "no strong features found. Skipping...";
        return;
    }

    metaData->homographyTransform = cv::findHomography(prevData.features, metaData->features, cv::RANSAC, cv::LMEDS);

    if (metaData->homographyTransform.empty()) {
        qDebug() << "no homography transsorm found. Skipping...";

        metaData->frame.copyTo(prevData.frame);
        metaData->overlay.copyTo(prevData.overlay);
        metaData->frameGrayscale.copyTo(prevData.frameGrayscale);

        return;
    }

    int dx = (-1) * metaData->homographyTransform.at<double>(0,2);
    int dy = (-1) * metaData->homographyTransform.at<double>(1,2);

    if ((qAbs(dx) > metaData->frame.cols) || (qAbs(dy) > metaData->frame.rows)) {
        qDebug() << "invalid homography transform. Skipping...";
        metaData->homographyTransform.at<double>(0,2) = 0;
        metaData->homographyTransform.at<double>(1,2) = 0;

        metaData->frame.copyTo(prevData.frame);
        metaData->overlay.copyTo(prevData.overlay);
        metaData->frameGrayscale.copyTo(prevData.frameGrayscale);

        return;
    }

    cv::swap(prevData.frame, metaData->frame);
    cv::swap(prevData.overlay, metaData->overlay);
    cv::swap(prevData.frameGrayscale, metaData->frameGrayscale);

    return;
}
