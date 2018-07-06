#ifndef STABILIZATIONFEATURES_HPP
#define STABILIZATIONFEATURES_HPP

#include <QObject>
#include "../VideoFilter.h"
#include <opencv2/opencv.hpp>

struct TransformParam
{
    TransformParam() {}
    TransformParam(double _dx, double _dy, double _da) {
        dx = _dx;
        dy = _dy;
        da = _da;
    }

    double dx;
    double dy;
    double da; // angle
};

struct Trajectory
{
    Trajectory() {
        x = 0;
        y = 0;
        a = 0;
    }
    Trajectory(double _x, double _y, double _a) {
        x = _x;
        y = _y;
        a = _a;
    }
    // "+"
    friend Trajectory operator+(const Trajectory &c1,const Trajectory  &c2){
        return Trajectory(c1.x+c2.x,c1.y+c2.y,c1.a+c2.a);
    }
    //"-"
    friend Trajectory operator-(const Trajectory &c1,const Trajectory  &c2){
        return Trajectory(c1.x-c2.x,c1.y-c2.y,c1.a-c2.a);
    }
    //"*"
    friend Trajectory operator*(const Trajectory &c1,const Trajectory  &c2){
        return Trajectory(c1.x*c2.x,c1.y*c2.y,c1.a*c2.a);
    }
    //"/"
    friend Trajectory operator/(const Trajectory &c1,const Trajectory  &c2){
        return Trajectory(c1.x/c2.x,c1.y/c2.y,c1.a/c2.a);
    }
    //"="
    Trajectory operator =(const Trajectory &rx){
        x = rx.x;
        y = rx.y;
        a = rx.a;
        return Trajectory(x,y,a);
    }

    void set(double _x, double _y, double _a) {
        x = _x;
        y = _y;
        a = _a;
    }

    double x;
    double y;
    double a; // angle
};

class StabilizationFeatures : public internalFrameFilter
{
public:
    StabilizationFeatures();

public slots:
    void processFrame(frameData* metaData);

private:
    double a;
    double x;
    double y;

    Trajectory X;   // posteriori state estimate
    Trajectory X_;  // priori estimate
    Trajectory P;   // posteriori estimate error covariance
    Trajectory P_;  // priori estimate error covariance
    Trajectory K;   // gain
    Trajectory z;   // actual measurement
    double pstd;    // can be changed
    double cstd;    // can be changed

    Trajectory Q;   // process noise covariance
    Trajectory R;   // measurement noise covariance

    std::vector <cv::Point2f> prev_corner, cur_corner;
    std::vector <uchar> status;
    std::vector <float> err;

    cv::Mat T, last_T;
};

#endif // STABILIZATIONFEATURES_HPP
