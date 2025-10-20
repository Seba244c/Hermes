import QtQuick
import QtQuick.Controls.Material


Rectangle {
    property int strokeLeft
    property int strokeTop
    property int strokeRight
    property int strokeBottom
    property var strokeColor: palette.light

    anchors.fill: parent
    color: "transparent"

    Rectangle {
        visible: strokeLeft
        width: strokeLeft
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        color: strokeColor
    }

    Rectangle {
        visible: strokeTop
        height: strokeTop
        anchors {
            left: parent.left
            top: parent.top
            right: parent.right
        }
        color: strokeColor
    }

    Rectangle {
        visible: strokeRight
        width: strokeRight
        anchors {
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
        color: strokeColor
    }

    Rectangle {
        visible: strokeBottom
        height: strokeBottom
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        color: strokeColor
    }
}
