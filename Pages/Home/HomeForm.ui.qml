import QtQuick 2.14
import QtQuick.Controls 2.14

import "../../App"
import "../../Components/"
import "../../Components/Buttons"
import "../../Components/FontAwesome"

Page {
    id: root

    property alias recordButton: recordButton

    width: Config.pageWidth
    height: Config.pageHeight

    title: qsTr("Home")

    Label {
        id: welcomeText
        anchors.horizontalCenter: recordButton.horizontalCenter
        anchors.bottom: recordButton.top
        anchors.bottomMargin: 10
        text: qsTr("Welcome to Prosody Meter")
        font.pointSize: 20
    }

    AnimatedRecordButton {
        id: recordButton
        anchors.centerIn: parent
        height: 200
        width: 200
    }
}
