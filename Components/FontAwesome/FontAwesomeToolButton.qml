import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: root

    property alias button: button
    property alias icon: awesome.icon
    property alias font: awesome.font
    property alias color: awesome.color
    property alias type: awesome.type

    property int baseSize: 22

    width: 32
    height: 32

    FontAwesomeIcon {
        id: awesome
        font.pointSize: button.hovered ? baseSize + 4 : baseSize
        anchors.centerIn: parent
    }

    ToolButton {
        id: button
        anchors.fill: parent
    }
}
