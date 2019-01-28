#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "CameraRreader.h"
#include "VideoItem.h"
#include "VideoPreprocessor.h"
#include "VideoFilter.h"

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::UMat>("cv::UMat");
    qmlRegisterType<CameraReader>("AIVCamera", 1, 0, "CameraReader");
    qmlRegisterType<VideoItem>("AIVCamera", 1, 0, "VideoItem");
    qmlRegisterType<VideoPreprocessor>("AIVCamera", 1, 0, "VideoPreprocessor");
    qmlRegisterType<VideoFilter>("AIVCamera", 1, 0, "VideoFilter");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
