import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Hermes.Models
import Hermes.Log

Window {
    id: main
    visible: true
    width: 1280
    height: 800
    title: "Hermes"
    color: palette.window

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
                // This is the name of the application and a menu button
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.fillWidth: true
                color: palette.mid

                Stroke {
                    strokeRight: 1
                    strokeColor: palette.light
                }
                Stroke {
                    strokeBottom: 1
                    strokeColor: palette.midlight
                }

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.centerIn: parent
                    spacing: 8
                    Layout.fillHeight: true

                    Text {
                        id: hermesTitle
                        verticalAlignment: Text.AlignVCenter
                        color: palette.text

                        text: qsTr("Hermes")
                        font.family: qsTr('Inter')
                        font.styleName: qsTr('Medium')
                        font.pixelSize: 28
                    }

                    Rectangle {
                        width: 35
                        height: 35
                        color: 'black'
                    }
                }
            }

            Rectangle {
                // places
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: palette.mid

                Stroke {
                    strokeRight: 1
                    strokeColor: palette.light
                }
            }
        }

        ColumnLayout { // Filelist and nagivation
            id: mainViewRight
            Layout.fillWidth: true
            clip: true

            spacing: 0

            NavigationBar {
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.fillWidth: true
            }

            FileListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
            }
        }
    }
}
