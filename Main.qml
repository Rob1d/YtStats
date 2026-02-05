import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "YtStats"

    Rectangle {
        anchors.fill: parent
        color: "#2C3E50"

    
        FileLoaderBtn {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
        }
    }
}
