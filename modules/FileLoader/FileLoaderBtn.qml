import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs


Item {
    width: 400
    height: 300

    FileLoader {
        id: fileLoader 
    }

    Button {
        id: loadButton
        text: "Loaded File " + fileLoader.fileName
        anchors.centerIn: parent
        onClicked: {
            fileLoader.openFileDialog()
        }
    }
}