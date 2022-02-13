import QtQuick 2.14
import QtQuick.Controls 2.14
import QtCharts 2.3
import QtQuick.Layouts 1.14

import "../../App"
import "../../Components"
import "../../Components/FontAwesome"

Page {
    id: root
    property alias wave: wave
    property alias waveSeries: waveSeries
    property alias pitchSeries: pitchSeries
    property alias pitchFullSeries: pitchFullSeries
    property alias octavesSeries: octavesSeries
    property alias octavesCategorisX: octavesCategorisX
    property alias octavesCategorisY: octavesCategorisY
    //property alias derivativeSeries: derivativeSeries
    //property alias derivativeCategorisX: derivativeCategorisX
    //property alias derivativeCategorisY: derivativeCategorisY
    property alias axisX: axisX
    property alias axisY: axisY
    property alias zoomInButton: zoomIn.button
    property alias zoomOutButton: zoomOut.button
    property alias zoomFitButton: zoomFit.button
    property alias octavesMax: octavesMax
    property alias octavesFullMax: octavesFullMax

    property alias showWaveSeriesSwitch: showWaveSeriesSwitch
    property alias showPitchSeriesSwitch: showPitchSeriesSwitch
    property alias showFullPitchSeriesSwitch: showFullPitchSeriesSwitch
    property alias showSegmentsSeriesSwitch: showSegmentsSeriesSwitch
    property bool showWaveSeries: false
    property bool showPitchSeries: true
    property bool showFullPitchSeries: false
    property bool showSegmentsSeries: true

    property double zoom: 1

    width: Config.pageWidth
    height: Config.pageHeight
    title: qsTr("Prosody")

    RowLayout {
        id: toolBar
        anchors.top: parent.top

        Switch {
            id: showWaveSeriesSwitch
            text: qsTr("Wave")
            checked: showWaveSeries
        }
        Switch {
            id: showPitchSeriesSwitch
            text: qsTr("Pitch")
            checked: showPitchSeries
        }
        Switch {
            id: showFullPitchSeriesSwitch
            text: qsTr("Full Pitch")
            checked: showFullPitchSeries
        }
        Switch {
            id: showSegmentsSeriesSwitch
            text: qsTr("Segments")
            checked: showSegmentsSeries
        }
    }

    ScrollView {
        id: scrollView
        anchors.top: toolBar.bottom
        contentHeight: wave.height + octaves.height + 50
        contentWidth: wave.width
        height: parent.height
        width: parent.width

        ValueAxis {
            id: axisY
            max: 1
            min: 0
            labelsVisible: true
            tickCount: 10
        }

        ValueAxis {
            id: axisX
            min: 0
            max: 1000
            labelsVisible: false
        }

        ChartView {
            id: wave
            height: 400
            width: axisX.max * root.zoom
            legend.visible: false

            margins.bottom: 0
            margins.top: 0
            margins.left: 40
            margins.right: 0

            LineSeries {
                id: waveSeries
                name: qsTr("Full wave")
                axisY: axisY
                axisX: axisX
                color: Colors.teal_blue
                visible: showWaveSeries
            }

            LineSeries {
                id: pitchSeries
                name: qsTr("Pitch")
                axisY: axisY
                axisX: axisX
                color: Colors.black
                width: 2
                visible: showPitchSeries && !showFullPitchSeries
            }

            LineSeries {
                id: pitchFullSeries
                name: qsTr("Pitch full")
                axisY: axisY
                axisX: axisX
                color: Colors.black
                width: 2
                visible: showPitchSeries && showFullPitchSeries
            }
        }

        /*ChartView {
            id: derivatives
            height: 400
            width: 150

            anchors.top: wave.bottom
            anchors.left: wave.left

            margins.bottom: 0
            margins.top: 0
            margins.left: 0
            margins.right: 0
            legend.visible: false

            BarSeries {
                id: derivativeSeries
                barWidth: 1
                axisX: BarCategoryAxis {
                    id: derivativeCategorisX
                    labelsFont.pointSize: 10
                    categories: ['&#9661;','=','&#9651;']
                }
                axisY: ValueAxis {
                    id: derivativeCategorisY
                    max: 1
                    min: 0
                    labelsFont.pointSize: 15
                }
            }
        }*/

        ChartView {
            id: octaves
            height: 400

            anchors.top: wave.bottom
            //anchors.left: derivatives.right
            anchors.left: wave.left
            anchors.right: wave.right

            margins.bottom: 0
            margins.top: 0
            margins.left: 0
            margins.right: 0

            BarSeries {
                id: octavesSeries
                barWidth: 1
                axisX: BarCategoryAxis {
                    id: octavesCategorisX
                    labelsFont.bold: true
                    labelsFont.pointSize: 15
                }
                axisY: ValueAxis {
                    id: octavesCategorisY
                    max: 1
                    min: 0
                    labelsFont.bold: true
                    labelsFont.pointSize: 15
                }
            }
        }

        Label {
            id: octavesMaxLabel
            text: qsTr("Record Max: ")
            font.pixelSize: 20
            color: "blue"
            anchors.top: octaves.top
            anchors.left: octaves.left
        }

        Label {
            id: octavesMax
            text: qsTr("0")
            font.pixelSize: 20
            color: "blue"
            anchors.top: octaves.top
            anchors.left: octavesMaxLabel.right
        }

        Label {
            id: octavesFullMaxLabel
            text: qsTr("Template Max: ")
            font.pixelSize: 20
            color: "green"
            anchors.top: octavesMax.bottom
            anchors.left: octaves.left
        }

        Label {
            id: octavesFullMax
            text: qsTr("0")
            font.pixelSize: 20
            color: "green"
            anchors.top: octavesMax.bottom
            anchors.left: octavesFullMaxLabel.right
        }
    }

    ColumnLayout {
        anchors.top: scrollView.top
        anchors.topMargin: 20
        anchors.left: scrollView.left
        anchors.leftMargin: 10
        spacing: 20

        FontAwesomeToolButton {
            id: zoomIn
            baseSize: 24
            color: Colors.black
            font.family: FontAwesome.regular
            icon: FontAwesome.icons.faPlusCircle
        }

        FontAwesomeToolButton {
            id: zoomFit
            baseSize: 24
            color: Colors.black
            font.family: FontAwesome.regular
            icon: FontAwesome.icons.faDotCircle
        }

        FontAwesomeToolButton {
            id: zoomOut
            baseSize: 24
            color: Colors.black
            font.family: FontAwesome.regular
            icon: FontAwesome.icons.faMinusCircle
        }
    }

}
