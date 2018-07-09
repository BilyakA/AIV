import QtQuick 2.10
import QtQuick.Window 2.10
import AIVCamera 1.0
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    CameraReader {
        id: imageProvider
        source: "rtsp://root:snorkel@192.168.243.118/axis-media/media.amp?videocodec=h264&amp;streamprofile=Quality"
        isFile: false
        crop: "2,2,698x568"

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

    VideoFilter {
        id: stabilizationFilter
        type: VideoFilter.STABILIZATION
        source: homographyPreprocessor
    }

    VideoFilter {
        id: panoramaFilter
        type: VideoFilter.STICHER
        source: homographyPreprocessor
    }

    TabView {
        anchors.fill: parent
        Tab {
            title: "source"
            VideoItem {
                id: videoOutputSource
                source: imageProvider
                anchors.fill: parent
            }
        }
        Tab {
            title: "stabilization"
            Item {
                anchors.fill: parent
                VideoItem {
                    id: videoOutputStabilizationOrig
                    source: imageProvider

                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    width: parent.width / 2
                }
                VideoItem {
                    id: videoOutputStabilization
                    source: stabilizationFilter

                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    width: parent.width / 2
                }
            }
        }
        Tab {
            title: "stiching"
            VideoItem {
                id: videoOutputSticher
                source: panoramaFilter
                anchors.fill: parent
            }
        }
    }
}
