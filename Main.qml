import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Hello Fedora 42 WASM"

    Rectangle {
        anchors.fill: parent
        color: "#2C3E50"

        Text {
            anchors.centerIn: parent
            text: "Qt QML running on ype"
            color: "white"
            font.pixelSize: 24
        }

        FileLoaderBtn {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
        }
    }
}
