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
    property alias octavesMarksSeries: octavesMarksSeries
    property alias octavesCategorisX: octavesCategorisX
    property alias octavesCategorisY: octavesCategorisY
    property alias octavesMarksCategorisX: octavesMarksCategorisX
    property alias octavesMarksCategorisY: octavesMarksCategorisY
    property alias derivativeSeries: derivativeSeries
    property alias derivativeCategorisX: derivativeCategorisX
    property alias derivativeCategorisY: derivativeCategorisY
    property alias axisX: axisX
    property alias axisY: axisY
    property alias zoomInButton: zoomIn.button
    property alias zoomOutButton: zoomOut.button
    property alias zoomFitButton: zoomFit.button
    property alias octavesMax: octavesMax
    property alias octavesFullMax: octavesFullMax
    property alias octavesRF0: octavesRF0
    property alias octavesDF0: octavesDF0
    property alias octavesAF0: octavesAF0
    property alias octavesTemplateRF0: octavesTemplateRF0
    property alias octavesTemplateDF0: octavesTemplateDF0
    property alias octavesTemplateAF0: octavesTemplateAF0

    property alias showWaveSeriesSwitch: showWaveSeriesSwitch
    property alias showPitchSeriesSwitch: showPitchSeriesSwitch
    property alias showFullPitchSeriesSwitch: showFullPitchSeriesSwitch
    property alias showSegmentsSeriesSwitch: showSegmentsSeriesSwitch
    property alias showMetricsSwitch: showMetricsSwitch
    property bool showMetrics: true
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
        Switch {
            id: showMetricsSwitch
            text: qsTr("CG0, CG1 & CG2")
            checked: showMetrics
        }
    }

    ScrollView {
        id: scrollView
        anchors.top: toolBar.bottom
        contentHeight: wave.height + octaves.height + 50
        contentWidth: wave.width
        height: parent.height
        width: parent.width
        bottomPadding: 50

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
            height: 150
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

        ColumnLayout {
            id: metrics
            anchors.top: wave.bottom
            anchors.left: wave.left
            anchors.right: wave.right
            visible: showMetrics

            height: showMetrics ? 50: 0

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Label {
                    text: qsTr("Record Max: ")
                    font.pixelSize: 20
                    color: "blue"
                }
                Label {
                    id: octavesMax
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "blue"
                }

                Label {
                    text: qsTr("R(F0): ")
                    font.pixelSize: 20
                    color: "blue"
                }
                Label {
                    id: octavesRF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "blue"
                }

                Label {
                    text: qsTr("D(F0): ")
                    font.pixelSize: 20
                    color: "blue"
                }
                Label {
                    id: octavesDF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "blue"
                }

                Label {
                    text: qsTr("A(F0): ")
                    font.pixelSize: 20
                    color: "blue"
                }
                Label {
                    id: octavesAF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "blue"
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Label {
                    text: qsTr("Template Max: ")
                    font.pixelSize: 20
                    color: "green"
                }
                Label {
                    id: octavesFullMax
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "green"
                }

                Label {
                    text: qsTr("R(F0): ")
                    font.pixelSize: 20
                    color: "green"
                }
                Label {
                    id: octavesTemplateRF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "green"
                }

                Label {
                    text: qsTr("D(F0): ")
                    font.pixelSize: 20
                    color: "green"
                }
                Label {
                    id: octavesTemplateDF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "green"
                }

                Label {
                    text: qsTr("A(F0): ")
                    font.pixelSize: 20
                    color: "green"
                }
                Label {
                    id: octavesTemplateAF0
                    text: qsTr("0")
                    font.pixelSize: 20
                    rightPadding: 15
                    color: "green"
                }
            }
        }

        ChartView {
            id: derivatives
            height: 350
            width: 100

            anchors.top: metrics.bottom
            anchors.left: metrics.left

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
                    labelsFont.pointSize: 8
                    labelsFont.bold: true
                    categories: ['+','-']
                }
                axisY: ValueAxis {
                    id: derivativeCategorisY
                    max: 1
                    min: 0
                    labelsFont.pointSize: 8
                    labelsFont.bold: true
                }
            }
        }

        ChartView {
            id: octaves
            height: 300

            anchors.top: metrics.bottom
            anchors.left: derivatives.right
            anchors.right: metrics.right

            margins.bottom: 0
            margins.top: 0
            margins.left: 0
            margins.right: 0

            legend.visible: false

            BarSeries {
                id: octavesSeries
                barWidth: 1
                axisX: BarCategoryAxis {
                    id: octavesCategorisX
                    labelsFont.bold: true
                    labelsFont.pointSize: 8
                }
                axisY: ValueAxis {
                    id: octavesCategorisY
                    max: 1
                    min: 0
                    labelsFont.bold: true
                    labelsFont.pointSize: 8
                }
            }
        }

        ChartView {
            id: octavesMarks
            height: 50

            anchors.top: octaves.bottom
            anchors.left: octaves.left
            anchors.right: octaves.right

            margins.bottom: 0
            margins.top: 0
            margins.left: 30
            margins.right: 0

            legend.visible: false

            BarSeries {
                id: octavesMarksSeries
                barWidth: 1
                axisX: BarCategoryAxis {
                    id: octavesMarksCategorisX
                    labelsFont.pointSize: 0
                    visible: false
                }
                axisY: ValueAxis {
                    id: octavesMarksCategorisY
                    labelsFont.pointSize: 8
                    max: 1
                    min: 0
                    tickCount: 2
                    visible: false
                }
            }
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
