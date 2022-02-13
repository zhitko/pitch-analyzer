import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

GridLayout {
    columns: 3
    columnSpacing: 10

    property var changed: null

    Text {
        id: label
        text: name
        font.bold: true
        font.pointSize: 15
        Layout.minimumWidth: 250
    }
    TextField {
        id: input
        text: value
        font.pointSize: 15
        Layout.alignment: Qt.AlignLeft
        visible: type !== "bool"
        onTextChanged: {
            input.text = changed(key, input.text)
        }
    }
    Switch {
        id: inputSwitch
        font.pointSize: 15
        checked: value === "true"
        visible: type === "bool"
        onCheckedChanged: {
            changed(key, inputSwitch.checked)
        }
    }
    Item {
        id: filler
        Layout.fillWidth: true
    }
    Text {
        id: descriptionHint
        text: description
        font.pointSize: 15
        font.italic: true
        Layout.columnSpan: 3
    }
}
