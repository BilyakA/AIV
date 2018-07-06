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

    VideoItem {
        id: videoOutput
        source: imageProvider
        anchors.fill: parent
    }
}
