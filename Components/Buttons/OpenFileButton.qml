import QtQuick 2.14

import "../../App"

OpenFileButtonForm {
    id: root

    button.onClicked: {
        console.log("Click open file button")
        Bus.openFileDialog()
    }
}
