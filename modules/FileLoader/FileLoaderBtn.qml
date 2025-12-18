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
            fileDialog.open()
        }
    }
    FileDialog {
        id: fileDialog
        title: "Select a File"
        
        nameFilters: ["Text files (*.txt)", "All files (*)"] 

        onAccepted: {
            console.log("You chose: " + fileDialog.currentFile)
            fileLoader.loadFile(fileDialog.currentFile)
        }

        onRejected: {
            console.log("File selection canceled")
        }
    }
}