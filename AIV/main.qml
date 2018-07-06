import QtQuick 2.10
import QtQuick.Window 2.10
import AIVCamera 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    CameraReader {
        id: imageProvider
        source: "rtsp://"
        isFile: false

        Component.onCompleted: {
            imageProvider.start()
        }
    }

    VideoPreprocessor {
        id: grayScalePreprocessor
        type: VideoPreprocessor.GRAYSCALE
        source: imageProvider
    }

    VideoPreprocessor {
        id: homographyPreprocessor
        type: VideoPreprocessor.HOMOGRAPHY
        source: grayScalePreprocessor
    }

    //VideoFilter {
    //    id: stabilizationFilter
    //    type: stabilization
    //}
    //
    //VideoFilter {
    //    id: panoramaFilter
    //    type: panorama
    //}

    VideoItem {
        id: videoOutput
        source: homographyPreprocessor
        anchors.fill: parent
    }
}
