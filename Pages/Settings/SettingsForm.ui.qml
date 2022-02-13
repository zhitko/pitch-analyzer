import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import "../../App"
import "../../Components"

Page {
    width: Config.pageWidth
    height: Config.pageHeight
    anchors.fill: parent

    property alias settingsModel: settingsModel

    title: qsTr("Settings")

    ListModel {
        id: settingsModel
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 10
        model: settingsModel
        spacing: 20
        delegate: SettingItem {
            changed: settingChanged
        }
    }
}
