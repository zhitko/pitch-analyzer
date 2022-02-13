import QtQuick 2.14

import "../../App"

PlayButtonForm {
    id: root

    Timer {
        id: timer
    }

    button.onClicked: {
        let interval = Bus.getRecordLength()

        if (interval === 0) return

        Bus.playRecord(root.playing)

        root.playing = !root.playing

        if (playing) {
            timer.interval = interval * 1000
            timer.repeat = false
            timer.triggered.connect(function(){
                root.playing = false
            })
            timer.start()
        } else {
            timer.stop()
        }
    }
}
