import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Hermes.Models

Window {
    visible: true
    width: 400
    height: 500
    title: "Hermes"

    FileListModel {
        id: fileListModel
    }

    ColumnLayout {
        id: fileListColumn
        anchors.fill: parent
        spacing: 0

        TextInput {
            id: pathInput
            text: fileListModel.currentPath

            Layout.fillWidth: true

            onAccepted: {
                fileListModel.currentPath = text
            }
        }

        ListView {
            id: fileList
            model: fileListModel

            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: Rectangle {
                width: parent ? parent.width : 0
                height: 40
                color: index % 2 === 0 ? "#f0f0f0" : "#ffffff"

                Row {
                    id: fileRow
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        id: fileName
                        text: name  // comes from model role
                        font.pointSize: 14
                    }
                }
            }
        }
    }
}
