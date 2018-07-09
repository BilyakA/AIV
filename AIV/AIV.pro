# prevent from running qmake three times (general, debug and release)
CONFIG -= debug_and_release

QT =
QT += core gui quick
CONFIG += c++11

SOURCES += \
        main.cpp        \
    CameraReader.cpp    \
    VideoItem.cpp       \
    FrameProvider.cpp \
    VideoPreprocessor.cpp \
    VideoFilter.cpp
HEADERS += \
    CameraRreader.h     \
    VideoItem.h         \
    FrameProvider.h \
    VideoPreprocessor.h \
    VideoFilter.h

SOURCES += \
    preprocessors/homography.cpp    \
    preprocessors/grayscale.cpp
HEADERS += \
    preprocessors/homography.h  \
    preprocessors/grayscale.h

SOURCES += \
    filters/panoramastitcher.cpp \
    filters/stabilizationfeatures.cpp
HEADERS += \
    filters/panoramastitcher.h \
    filters/stabilizationfeatures.hpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$BUILD_PWD/third_party/build/include
LIBS += -L$$BUILD_PWD/third_party/build/lib

LIBS += -lopencv_core -lopencv_videoio -lopencv_imgproc \
    -lopencv_video -lopencv_tracking -lopencv_videostab -lopencv_features2d \
    -lopencv_saliency -lopencv_calib3d
