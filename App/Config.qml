pragma Singleton
import QtQuick 2.14

Item {
    readonly property int pageWidth: 600
    readonly property int pageHeight: 400

    readonly property int applicationWidth: pageWidth + 40
    readonly property int applicationHeight: pageHeight + 80
}
