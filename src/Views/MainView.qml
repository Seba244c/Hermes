import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Hermes.Models
import Hermes.Log

Window {
    visible: true
    width: 1280
    height: 800
    title: "Hermes"

    FileListModel {
        id: fileListModel
    }

    Logger {
        id: logger
    }

    // The main view is split up into to columns
    // The left column is for places
    // The right column is for the filelist and navigation
    RowLayout {
        anchors.fill: parent
        spacing: 0

        ColumnLayout {
            id: mainViewLeft
            Layout.preferredWidth: 200
            Layout.maximumWidth: 200

            spacing: 0

            Rectangle {
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.fillWidth: true
                color: 'red'
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: 'blue'
            }
        }

        ColumnLayout {
            id: mainViewRight
            Layout.fillWidth: true

            spacing: 0

            TextInput {
                id: pathInput
                text: fileListModel.currentPath

                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.fillWidth: true

                onAccepted: {
                    fileListModel.currentPath = text;
                }
            }

            FileListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
