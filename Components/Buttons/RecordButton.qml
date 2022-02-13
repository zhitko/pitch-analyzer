import QtQuick 2.14

import intondemo.backend 1.0

import "../../App"

RecordButtonForm {
    id: root

    button.onClicked: {
        Bus.goRecording()
    }
}
