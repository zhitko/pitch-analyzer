import QtQuick 2.14
import QtQuick.Controls 2.14

import "../../App"

SettingsForm {
    id: root
    objectName: Enum.pageSettings

    StackView.onActivated: {
        console.log("SettingsForm.StackView.onActivated")
        Bus.hideAllBottomActions()

        loadSettings()
    }

    function loadSettings() {
        let settings = Bus.getSettings()
        console.log("SettingsForm.loadSettings", settings)
        settingsModel.clear()
        for (let i in settings){
            settingsModel.append(
                {
                    "name": settings[i].name,
                    "description": settings[i].description,
                    "value": settings[i].value,
                    "key": settings[i].key,
                    "type": settings[i].type
                }
            )
            console.log(settings[i].key, settings[i].name, settings[i].value)
        }
    }

    function settingChanged(name, value) {
        console.log("Settings Page: ", name, value)
        return Bus.setSettings(name, value)
    }

}
