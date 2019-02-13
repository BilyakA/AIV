#include "stabilizationfeatures.h"

StabilizationFeatures::StabilizationFeatures()
    // Accumulated frame to frame transform
    : a(0)
    , x(0)
    , y(0)
{
    pstd = 4e-3;
    cstd = 0.25;

    Q.set(pstd, pstd, pstd); // process noise covariance
    R.set(cstd, cstd, cstd); // measurement noise covariance

    X = Trajectory(0,0,0); //Initial estimate,  set 0
    P = Trajectory(1,1,1); //set error variance,set 1
}

// TODO: filter out collinuar points
void StabilizationFeatures::processFrame(frameData *metaData)
{
    // in rare cases no transform is found. We'll just use the last known good transform.
    if(metaData->homographyTransform.empty()) {
        if (last_T.empty()) {

            qDebug() << "no current or previous transformation found, skipping!";
            return;
        }
        last_T.copyTo(T);
    } else {
        metaData->homographyTransform(cv::Rect(0,0,3,2)).copyTo(T);
    }

    // decompose T
    double dx = T.at<double>(0,2);
    double dy = T.at<double>(1,2);
    double da = atan2(T.at<double>(1,0), T.at<double>(0,0));

    // Accumulated frame to frame transform
    x += dx;
    y += dy;
    a += da;
    z = Trajectory(x,y,a);

    //time update（prediction）
    X_ = X; //X_(k) = X(k-1);
    P_ = P + Q; //P_(k) = P(k-1)+Q;
    // measurement update（correction）
    K = P_ / ( P_ + R ); //gain;K(k) = P_(k)/( P_(k)+R );
    X = X_ + K * ( z  -X_ ); //z-X_ is residual,X(k) = X_(k)+K(k)*(z(k)-X_(k));
    P = (Trajectory(1,1,1) - K ) * P_; //P(k) = (1-K(k))*P_(k);

    // target - current
    double diff_x = X.x - x;//
    double diff_y = X.y - y;
    double diff_a = X.a - a;

    dx = dx + diff_x;
    dy = dy + diff_y;
    da = da + diff_a;

    T.at<double>(0,0) = cos(da);
    T.at<double>(0,1) = -sin(da);
    T.at<double>(1,0) = sin(da);
    T.at<double>(1,1) = cos(da);

    T.at<double>(0,2) = dx;
    T.at<double>(1,2) = dy;

    cv::UMat cur2;
    cv::UMat cur2_disp;

    //cv::warpPerspective(prevData.frame, cur2, T, metaData->frame.size());
    ////cv::imshow("perspective", cur2);
    //cv::warpPerspective(prevData.overlay, cur2_disp, T, metaData->frame.size());

    T.copyTo(last_T);
    cv::warpAffine(metaData->frame, cur2, T, metaData->frame.size());
    if (!metaData->overlay.empty()) {
        cv::warpAffine(metaData->overlay, cur2_disp, T, metaData->frame.size());
    }

    metaData->frame = cur2;
    if (!metaData->overlay.empty()) {
        metaData->overlay = cur2_disp;
    }

    return;
}
