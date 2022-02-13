import QtQuick 2.4

import "../../App"

AnimatedRecordButtonForm {
    id: root

    property int frame: 0

    Timer {
        id: timer
        interval: 500;
        repeat: true
        onTriggered: {
            root.icon.source = "qrc:/Assets/Images/speech-active-%1-icon.png".arg(frame)
            frame ++
            if (frame > 3) frame = 0
        }
    }

    onCheckedChanged: {
        if (checked)
        {
            Bus.startRecord()
            timer.start()
            root.icon.source = "qrc:/Assets/Images/speech-active-0-icon.png"
        } else {
            Bus.stopRecord()
            timer.stop()
            root.icon.source = "qrc:/Assets/Images/speech-icon.png"
        }
    }
}
