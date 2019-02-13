#include "peopledetect.h"

ProcessorPeopleDetect::ProcessorPeopleDetect()
{
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    //hog.setSVMDetector(cv::HOGDescriptor::getDaimlerPeopleDetector());
}

void ProcessorPeopleDetect::processFrame(frameData* metaData)
{
    std::vector<cv::Rect> found;

    if (metaData->frame.empty()) {
        qWarning() << "Empty frame as input to people detect processor";
        return;
    }

    hog.detectMultiScale(metaData->frame, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2, false);

    for (std::vector<cv::Rect>::iterator i = found.begin(); i != found.end(); ++i)
    {
        cv::Rect &r = *i;
        adjustRect(r);
        rectangle(metaData->frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
    }
    //imshow("People detector", frame);

    return;
}

void ProcessorPeopleDetect::adjustRect(cv::Rect & r) const
{
    // The HOG detector returns slightly larger rectangles than the real objects,
    // so we slightly shrink the rectangles to get a nicer output.
    r.x += cvRound(r.width*0.1);
    r.width = cvRound(r.width*0.8);
    r.y += cvRound(r.height*0.07);
    r.height = cvRound(r.height*0.8);
}
