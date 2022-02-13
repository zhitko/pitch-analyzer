import QtQuick 2.14
import QtQuick.Controls 2.14

import "../../App"

RecordForm {
    objectName: Enum.pageRecord

    StackView.onActivated: {
        console.log("RecordForm.StackView.onActivated")
        Bus.hideAllBottomActions()
    }
}
