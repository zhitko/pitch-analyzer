import QtQuick 2.14
import QtQuick.Controls 2.14
import QtCharts 2.14

import "../../Components"
import "../../App"

PitchForm {
    id: root
    objectName: Enum.pagePitch

    property var waveSegments: []
    property var recordOctavesData: []
    property var recordFullOctavesData: []
    property var templateOcatavesData: []
    property var templateFullOcatavesData: []
    property var octavesCategories: []
    property int recordOctavesMax: 0
    property int recordFullOctavesMax: 0
    property int templateOcatavesMax: 0
    property int templateFullOcatavesMax: 0

    property bool calculatedWaveSeries: false
    property bool calculatedPitchSeries: false

    property bool calculatedSegmentsSeries: false
    property bool calculatedFullPitchSeries: false

    property int minPitch: 0
    property int maxPitch: 1

    StackView.onActivated: {
        console.log("PitchForm.StackView.onActivated")
        Bus.hideAllBottomActions()
        Bus.showPlayButton = Bus.recordPath !== ""
        Bus.showRecordButton = true
        Bus.showOpenButton = true
        Bus.showOpenTemplateButton = true

        calculatedWaveSeries = false
        calculatedPitchSeries = false
        calculatedSegmentsSeries = false
        calculatedFullPitchSeries = false

        clearAll()

        if (root.showWaveSeries) showWave()
        if (root.showSegmentsSeries) showSegments()
        if (root.showPitchSeries) showPitch()

        showOctaves()
        showDerivatives()
        showOctavesMetrics()
        showOctavesMarks()

        let pitchMinMax = Bus.getPitchMinMax()
        root.minPitch = pitchMinMax.x
        root.maxPitch = pitchMinMax.y

        axisY.min = root.minPitch
        axisY.max = root.maxPitch

        console.log("minPitch = ", minPitch)
        console.log("maxPitch = ", maxPitch)

        fitZoom()
    }

    function showOctaves() {
        root.octavesSeries.clear()
        if (root.showFullPitchSeries) {
            showFullRecordOctaves()
            showFullTemplateOctaves()
        } else {
            showRecordOctaves()
            showTemplateOctaves()
        }
    }

    function showRecordOctaves() {
        console.log("PitchForm.showOctaves")

        recordOctavesData = []

        let data = Bus.getOctavesData()
        console.log("getOctavesData", data)
        if (data.length === 0) return;

        octavesCategories = []
        let max = 0
        for (let i=0; i< data.length - 1; i++) {
            console.log("value: ", data[i])
            octavesCategories.push(i+1)
            recordOctavesData.push(data[i])
            if (data[i] > max) max = data[i]
        }
        console.log("octavesCategories", octavesCategories)
        console.log("max", max)

        recordOctavesMax = data[data.length - 1]

        octavesCategorisX.categories = octavesCategories
        octavesMarksCategorisX.categories = octavesCategories
        octavesCategorisY.max = max

        octavesMax.text = recordOctavesMax
        octavesSeries.append("Record", recordOctavesData)
    }

    function showFullRecordOctaves() {
        console.log("PitchForm.showFullOctaves")

        recordFullOctavesData = []

        let data = Bus.getFullOctavesData()
        console.log("getFullOctavesData", data)
        if (data.length === 0) return;

        octavesCategories = []
        let max = 0
        for (let i=0; i< data.length - 1; i++) {
            console.log("value: ", data[i])
            octavesCategories.push(i+1)
            recordFullOctavesData.push(data[i])
            if (data[i] > max) max = data[i]
        }
        console.log("octavesCategories", octavesCategories)
        console.log("max", max)

        recordFullOctavesMax = data[data.length - 1]

        octavesCategorisX.categories = octavesCategories
        octavesMarksCategorisX.categories = octavesCategories
        octavesCategorisY.max = max

        octavesMax.text = recordFullOctavesMax
        octavesSeries.append("Record", recordFullOctavesData)
    }

    function showTemplateOctaves() {
        console.log("PitchForm.showTemplateOctaves")

        templateOcatavesData = []

        let data = Bus.getTemplateOctavesData()
        console.log("getTemplateOctavesData", data)

        octavesCategories = []
        let max = 0
        if (data.length !== 0) {
            for (let i=0; i< data.length - 1; i++) {
                console.log("value: ", data[i])
                octavesCategories.push(i+1)
                templateOcatavesData.push(data[i])
                if (data[i] > max) max = data[i]
            }
            console.log("filledFullOctaves", octavesCategories)
            console.log("max", max)

            if (data.length > 0) {
                templateOcatavesMax = data[data.length - 1]

                octavesCategorisX.categories = octavesCategories
                octavesMarksCategorisX.categories = octavesCategories
                octavesCategorisY.max = max
            }

        }
        octavesFullMax.text = templateOcatavesMax
        octavesSeries.append("Template", templateOcatavesData)
    }

    function showFullTemplateOctaves() {
        console.log("PitchForm.showFullTemplateOctaves")

        templateFullOcatavesData = []

        let data = Bus.getFullTemplateOctavesData()
        console.log("getFullTemplateOctavesData", data)

        octavesCategories = []
        let max = 0
        for (let i=0; i< data.length - 1; i++) {
            console.log("value: ", data[i])
            octavesCategories.push(i+1)
            templateFullOcatavesData.push(data[i])
            if (data[i] > max) max = data[i]
        }
        console.log("octavesCategories", octavesCategories)
        console.log("max", max)

        if (data.length > 0) {
            templateFullOcatavesMax = data[data.length - 1]

            octavesCategorisX.categories = octavesCategories
            octavesMarksCategorisX.categories = octavesCategories
            octavesCategorisY.max = max
        }

        octavesFullMax.text = templateFullOcatavesMax
        octavesSeries.append("Template", templateFullOcatavesData)
    }

    function showWave() {
        console.log("PitchForm.showWave")

        let data = Bus.getWaveData()
        axisX.max = data[data.length - 1].x
        addDataToSeries(waveSeries, data)

        root.calculatedWaveSeries = true
    }

    function showSegments() {
        console.log("PitchForm.showSegments")

        let data = Bus.getSegmentsByIntensity()
        addSegmentsToSeries(
            Colors.setAlpha(Colors.green, "40"),
            "segments",
            data,
            root.waveSegments
        )

        root.calculatedSegmentsSeries = true
    }

    function showPitch() {
        console.log("PitchForm.showPitch")

        let data = Bus.getPitchData()
        console.log("PitchForm.showPitch data = ", !!data)
        if (!data || data.length === 0) return
        axisX.max = data[data.length - 1].x

        console.log("PitchForm.showPitch", data.length)
        addDataToSeries(pitchSeries, data)

        root.calculatedPitchSeries = true
    }

    function showDerivatives() {
        console.log("PitchForm.showDerivatives", root.showFullPitchSeries)
        root.derivativeSeries.clear()

        let recordData = Bus.getDerivativeData(root.showFullPitchSeries)
        derivativeSeries.append("Record", recordData)

        let templateData = Bus.getTemplateDerivativeData(root.showFullPitchSeries)
        derivativeSeries.append("Template", templateData)
    }

    function showOctavesMarks() {
        console.log("PitchForm.showOctavesMarks")
        root.octavesMarksSeries.clear()

        let recordData = Bus.getPitchOcavesMetrics(root.showFullPitchSeries)
        console.log("PitchForm.showOctavesMarks recordData", recordData)
        let recordSeries = []
        for (let i in octavesCategorisX.categories) {
            recordSeries.push(0)
        }
        if (!!recordData[0]) recordSeries[recordData[0]-1] = 1
        if (!!recordData[1]) recordSeries[recordData[1]-1] = 1
        if (!!recordData[2]) recordSeries[recordData[2]-1] = 1
        console.log("PitchForm.showOctavesMarks Record", recordSeries)
        root.octavesMarksSeries.append("Record", recordSeries)

        let templateData = Bus.getTemplateOcavesMetrics(root.showFullPitchSeries)
        console.log("PitchForm.showOctavesMarks templateData", templateData)
        let templateSeries = []
        for (let j in octavesCategorisX.categories) {
            templateSeries.push(0)
        }
        if (!!templateData[0]) templateSeries[templateData[0]-1] = 1
        if (!!templateData[1]) templateSeries[templateData[1]-1] = 1
        if (!!templateData[2]) templateSeries[templateData[2]-1] = 1
        console.log("PitchForm.showOctavesMarks Template", templateSeries)
        root.octavesMarksSeries.append("Template", templateSeries)
    }

    function showOctavesMetrics() {
        console.log("PitchForm.showOctavesMetrics", root.showFullPitchSeries)

        let recordData = Bus.getPitchOcavesMetrics(root.showFullPitchSeries)
        if (!!recordData[0]) root.octavesRF0.text = recordData[0]
        if (!!recordData[3]) root.octavesDF0.text = recordData[3]
        if (!!recordData[4]) root.octavesAF0.text = recordData[4]

        let templateData = Bus.getTemplateOcavesMetrics(root.showFullPitchSeries)
        if (!!templateData[0]) root.octavesTemplateRF0.text = templateData[0]
        if (!!templateData[3]) root.octavesTemplateDF0.text = templateData[3]
        if (!!templateData[4]) root.octavesTemplateAF0.text = templateData[4]
    }

    function showFullPitch() {
        console.log("PitchForm.showFullPitch")

        let data = Bus.getFullPitchData()
        console.log("PitchForm.showFullPitch data = ", !!data)
        if (!data || data.length === 0) return
        axisX.max = data[data.length - 1].x

        console.log("PitchForm.showFullPitch", data.length)
        addDataToSeries(pitchFullSeries, data)

        root.calculatedFullPitchSeries = true
    }

    function clearAll() {
        root.waveSeries.clear()
        root.pitchSeries.clear()
        root.waveSegments.forEach(l => l.clear())
    }

    function addDataToSeries(serias, data) {
        serias.clear()
        for (let value in data){
            serias.append(data[value].x, data[value].y)
        }
    }

    function addSegmentsToSeries(color, seriesName, data, collection) {
        console.log(seriesName + " segmants count: " + data.length)

        for(let i in data) {
            collection.push(addSeries(
                wave,
                axisX,
                axisY,
                color,
                true,
                999,
                seriesName,
                [{x:data[i].x, y:0}, {x:data[i].y, y:0}]
            ))
        }
    }

    function addSeries(chart, seriesX, seriesY, color, isVisible, width, seriesName, data) {
        var line = chart.createSeries(ChartView.SeriesTypeLine, seriesName, seriesX, seriesY)
        line.width = width
        line.color = color
        line.pointsVisible = false
        line.capStyle = "FlatCap"
        line.visible = isVisible
        for(let i in data) {
            line.append(data[i].x, data[i].y)
        }
        return line;
    }

    function fitZoom() {
        root.zoom = root.width / axisX.max
    }

    zoomInButton.onClicked: {
        root.zoom += 0.1
    }

    zoomOutButton.onClicked: {
        root.zoom -= 0.1
    }

    zoomFitButton.onClicked: {
        fitZoom()
    }

    showWaveSeriesSwitch.onCheckedChanged: {
        root.showWaveSeries = showWaveSeriesSwitch.checked

        if (root.showWaveSeries && !root.calculatedWaveSeries) {
            showWave()
        }

        if (root.showWaveSeries) {
            axisY.max = root.maxPitch
            axisY.min = -1
        } else {
            axisY.max = root.maxPitch
            axisY.min = root.minPitch
        }
    }

    showPitchSeriesSwitch.onCheckedChanged: {
        root.showPitchSeries = showPitchSeriesSwitch.checked
        console.log("showPitchSeriesSwitch: ", showPitchSeries)

        if (root.showPitchSeries && !root.calculatedPitchSeries) {
            showPitch()
        }
    }

    showFullPitchSeriesSwitch.onCheckedChanged: {
        showFullPitchSeries = showFullPitchSeriesSwitch.checked
        console.log("showFullPitchSeriesSwitch: ", showFullPitchSeries)
        root.showPitchSeries = true

        if (root.showFullPitchSeries && !root.calculatedFullPitchSeries) {
            showFullPitch()
        } else if (!root.showFullPitchSeries && !root.calculatedPitchSeries) {
            showPitch()
        }

        showOctaves()
        showDerivatives()
        showOctavesMetrics()
        showOctavesMarks()
    }

    showSegmentsSeriesSwitch.onCheckedChanged: {
        root.showSegmentsSeries = showSegmentsSeriesSwitch.checked

        if (root.showSegmentsSeries && !root.calculatedSegmentsSeries) {
            showSegments()
        }

        root.waveSegments.forEach(l => l.visible = root.showSegmentsSeries)
    }


    showMetricsSwitch.onCheckedChanged: {
        root.showMetrics = showMetricsSwitch.checked
    }
}
