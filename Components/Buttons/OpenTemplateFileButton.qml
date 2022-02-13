import QtQuick 2.14

import "../../App"

OpenTemplateFileButtonForm {
    id: root

    button.onClicked: {
        console.log("Click open file button")
        Bus.openTemplateFileDialog()
    }
}
