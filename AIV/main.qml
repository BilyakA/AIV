import QtQuick 2.10
import QtQuick.Window 2.10
import AIVCamera 1.0
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("AIV DEMO")

    CameraReader {
        id: videoSource
        //source: "rtsp://"
        //device: 0 + CameraReader.CAP_DSHOW
        device: 0
        isFile: false
        //crop: "2,2,698x568"

        Component.onCompleted: {
            videoSource.start()
        }
    }

    VideoItem {
        id: videoOutput
        source: videoSource
        anchors.fill: parent
    }

    VideoStreamer {
        id: videoStreamer
        source: videoSource
    }

}
