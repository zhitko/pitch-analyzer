import QtQuick 2.4
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import "Buttons"
import "../App"

ToolBar {
    id: root

    GridLayout {
        anchors.fill: parent

        RecordButton {
            id: recordButton
            visible: Bus.showRecordButton && Bus.canRecordButton
            Layout.alignment: Qt.AlignCenter
        }

        PlayButton {
            id: playButton
            visible: Bus.showPlayButton && Bus.canPlayButton
            Layout.alignment: Qt.AlignCenter
        }

        OpenFileButton {
            id: openButton
            visible: Bus.showOpenButton && Bus.canOpenButton
            Layout.alignment: Qt.AlignCenter
        }

        OpenTemplateFileButton {
            id: openTemplateButton
            visible: Bus.showOpenTemplateButton && Bus.canOpenTemplateButton
            Layout.alignment: Qt.AlignCenter
        }
    }
}
