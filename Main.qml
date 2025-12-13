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
            text: "Qt QML running on WebAssembly!"
            color: "white"
            font.pixelSize: 24
        }

        Button {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20
            text: "Click Me"
            onClicked: parent.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
        }
    }
}
