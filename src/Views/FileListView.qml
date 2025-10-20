import QtQuick
import QtQuick.Layouts
import Hermes.Models
import Hermes.Log

ListView {
    id: fileList
    model: fileListModel

    delegate: Rectangle {
        width: parent ? parent.width : 0
        height: 40
        color: index % 2 === 0 ? palette.base : palette.alternateBase

        RowLayout {
            id: fileRow
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter

            Item {}
            Text {
                id: fileName
                text: name  // comes from model role
                font.pointSize: 11
                color: palette.text
            }
            Item{}
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: isFolder ? Qt.PointingHandCursor : Qt.ArrowCursor

            onDoubleClicked: {
                fileListModel.Open(name + (isFolder ? "/" : ""));
            }
        }
    }
}
