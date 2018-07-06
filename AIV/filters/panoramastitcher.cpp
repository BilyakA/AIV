#include "panoramastitcher.h"

PanoramaStitcher::PanoramaStitcher()
{

}

void PanoramaStitcher::processFrame(frameData *metaData)
{
    if (metaData->frame.empty()) {
        return;
    }

    if (panorama.empty()) {
        panorama = cv::UMat::zeros(metaData->frame.rows, metaData->frame.cols, CV_8UC3);
    }

    if (metaData->homographyTransform.empty()) {
        return;
    }

    int dx = (-1) * metaData->homographyTransform.at<double>(0,2);
    int dy = (-1) * metaData->homographyTransform.at<double>(1,2);
    //qDebug() << "dx = " << dx << " dy = " << dy;

    ROI.x += dx;
    ROI.y += dy;
    ROI.width = metaData->frame.size().width;
    ROI.height = metaData->frame.size().height;
    //panoramaSize.width = metaData->homographyTransform.at<double>(0,2) + panorama.size().width;

    cv::Size2i panoramaSize = panorama.size();
    cv::Rect2i panoramaPos = cv::Rect2i(0, 0, panorama.size().width, panorama.size().height);

    if (ROI.x < 0) {
        panoramaSize.width -= ROI.x; // enlarge panoramaSize.width
        panoramaPos.x = (-1) * ROI.x;
        ROI.x = 0;
    } else if (ROI.x + ROI.width > panoramaSize.width) {
        panoramaSize.width += (ROI.x + ROI.width) - panoramaSize.width;
    }
    if (ROI.y < 0) {
        panoramaSize.height -= ROI.y; // enlarge panoramaSize.height
        panoramaPos.y = (-1) * ROI.y;
        ROI.y = 0;
    } else if (ROI.y + ROI.height > panoramaSize.height) {
        panoramaSize.height += (ROI.y + ROI.height) - panoramaSize.height;
    }

    if (panoramaSize != panorama.size()) {
        cv::UMat frame(panoramaSize, CV_8UC3);
        //cv::resize(panorama, frame, panoramaSize, 1, 1);
        panorama.copyTo(frame(panoramaPos));
        panorama = frame;
    }

    metaData->frame.copyTo(panorama(ROI));
    //if ( (metaData->displayFrame.size().width  < panorama.size().width) ||
    //     (metaData->displayFrame.size().height < panorama.size().height)) {
    //    cv::Mat img_dst;
    //    cv::resize(metaData->displayFrame, img_dst, panorama.size(),
    //}
    //cv::imshow("panorama", panorama);
    metaData->frame = panorama;

    return;
}
