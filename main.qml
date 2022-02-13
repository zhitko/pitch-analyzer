import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import "App"
import "Components"
import "Components/FontAwesome"

ApplicationWindow {
    id: window
    width: Config.applicationWidth
    height: Config.applicationWidth
    visible: true
    title: qsTr("Prosody Meter")

    Component.onCompleted: {
        Bus.stackView = stackView
        Bus.goHome()
    }

    StackView {
        id: stackView
        anchors.fill: parent
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        RowLayout {
            anchors.fill: parent


            FontAwesomeToolButton {
                id: menuButton
                type: FontAwesome.solid
                icon: FontAwesome.icons.faBars
                Layout.alignment: Qt.AlignLeft
                button.onClicked: drawer.open()
                Layout.margins: 10
            }

            FontAwesomeToolButton {
                id: toolButton
                type: FontAwesome.solid
                icon: FontAwesome.icons.faArrowLeft
                Layout.alignment: Qt.AlignRight
                visible: stackView.depth > 1
                button.onClicked: Bus.goBack()
                Layout.margins: 10
            }
        }

        Label {
            text: stackView.currentItem ? stackView.currentItem.title : ""
            anchors.centerIn: parent
        }
    }

    footer: BottomBar {
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Home")
                width: parent.width
                onClicked: {
                    Bus.goHome()
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Recording")
                width: parent.width
                onClicked: {
                    Bus.goRecord()
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Prosody")
                width: parent.width
                onClicked: {
                    Bus.goPith()
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    Bus.goSettings()
                    drawer.close()
                }
            }
        }
    }
}
