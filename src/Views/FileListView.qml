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
        color: index % 2 === 0 ? "#f0f0f0" : "#ffffff"

        RowLayout {
            id: fileRow
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: fileName
                text: name  // comes from model role
                font.pointSize: 14
            }
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
