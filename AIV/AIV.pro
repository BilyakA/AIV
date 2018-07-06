# prevent from running qmake three times (general, debug and release)
CONFIG -= debug_and_release

QT =
QT += core gui quick
CONFIG += c++11

SOURCES += \
        main.cpp \
    CameraReader.cpp \
    VideoItem.cpp \
    FrameProvider.cpp

HEADERS += \
    CameraRreader.h \
    VideoItem.h \
    FrameProvider.h

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$BUILD_PWD/third_party/build/include
LIBS += -L$$BUILD_PWD/third_party/build/lib

LIBS += -lopencv_core -lopencv_videoio -lopencv_imgproc

