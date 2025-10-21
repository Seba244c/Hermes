import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Hermes.Models
import Hermes.Log

Rectangle {
    Layout.minimumHeight: 50
    Layout.preferredHeight: 50
    Layout.fillWidth: true
    color: palette.base

    RowLayout {
        // Navigation
        anchors.fill: parent
        spacing: 10
        z: 8

        Item {}
        ToolButton {
            // Go up
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            flat: true
            enabled: engine.canGoUp

            icon.source: "qrc:/qt/qml/Hermes/resources/icons/double-back.svg"
            icon.color: enabled ? palette.text : palette.highlightedText

            background: Rectangle {
                color: parent.hovered ? palette.highlightedText : "transparent"  // subtle hover effect
                radius: 4
            }

            onClicked: {
                engine.GoUp();
            }
        }

        RowLayout {
            // Forward and back are closer together
            Layout.fillHeight: true
            spacing: 4
            ToolButton {
                Layout.preferredHeight: 30
                Layout.preferredWidth: 30
                flat: true
                enabled: engine.canGoBack

                icon.source: "qrc:/qt/qml/Hermes/resources/icons/back.svg"
                icon.color: enabled ? palette.text : palette.highlightedText

                background: Rectangle {
                    color: parent.hovered && parent.enabled ? palette.highlightedText : "transparent"  // subtle hover effect
                    radius: 4
                }

                onClicked: {
                    engine.GoBack();
                }
            }
            ToolButton {
                Layout.preferredHeight: 30
                Layout.preferredWidth: 30
                flat: true
                enabled: engine.canGoForward

                icon.source: "qrc:/qt/qml/Hermes/resources/icons/forward.svg"
                icon.color: enabled ? palette.text : palette.highlightedText

                background: Rectangle {
                    color: parent.hovered && parent.enabled ? palette.highlightedText : "transparent"  // subtle hover effect
                    radius: 4
                }
                onClicked: {
                    engine.GoForward();
                }
            }
        }

        Rectangle {
            // Path
            Layout.preferredHeight: 30
            Layout.minimumWidth: 100
            Layout.fillWidth: true
            z: 10
            radius: 10
            color: palette.midlight
            TextInput {
                id: pathInput
                anchors.verticalCenter: parent.verticalCenter
                x: 10
                z: 10
                width: parent.width - 20

                text: fileListModel.currentPath
                color: palette.text
                selectionColor: palette.highlightedText
                onAccepted: {
                    engine.SetCurrentPath(text);
                }
            }
        }

        Item {}
    }
}
