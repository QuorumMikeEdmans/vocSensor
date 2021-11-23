import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtCharts 2.1
import quorum.VocSensor 1.0


Window {
    visible: true
    width: 800
    height: 480
    property int sampleX:0
    property int xMax:10
    property int yMax:3
    property string sensorDisplayString
    property real vocReading:VocSensor.VocReading
    property real maxReading:0.5
    property int spinBoxHeight: 40
    property int spinBoxTextHeight:24
    property bool samplingInProgress:false
    property bool messageBoxVisible:false
    property string messageBoxText: "Message"

    title: qsTr("VOC Sensor monitor")
    onMessageBoxVisibleChanged: disappearTimer.start(5000)

        Timer{
            id: disappearTimer
            interval:5000
            repeat:false
            onTriggered: messageBoxVisible=false
        }

    Rectangle{
        anchors.fill: parent
        z:99
        gradient: Gradient {
            GradientStop {position: 0; color: "#7FA4EF"}
            GradientStop {position: 0.5; color: "#4F81BD"}
        }
        Rectangle{
            x:500
            y:300
            z:100
            border.color: "black"
            border.width: 2
            height:60
            width:150
            radius:5
            color:"lightsteelblue"

            visible:messageBoxVisible
                        Text{
                            anchors.fill: parent
                            anchors.margins: 10
                            text: messageBoxText
                        }
                        Connections{
                            target: VocSensor
                            onNewMessage:
                            {
                                messageBoxText=message
                                messageBoxVisible=true
                            }
                        }

        }

        Row{
            id: row
            leftPadding: 20
            spacing:25

            Column
            {
                spacing:10
                leftPadding: 10
                topPadding: 50

                CircularGauge {
                    id: gauge
                    width:220
                    height:220
                    tickmarksVisible: true
                    maximumValue: 10
                    value: vocReading
                    stepSize: 0.05

                    style: CircularGaugeStyle{
                        tickmarkStepSize: 1
                        minorTickmarkCount: 5
                        tickmarkLabel:  Text {
                            font.pixelSize: 20
                            text: styleData.value
                            color: "white"
                            antialiasing: true
                        }
                        tickmarkInset:-10
                        minorTickmarkInset:-10
                        tickmark: Rectangle {
                            width: 2
                            height: 20
                            color:"white"
                        }
                        minorTickmark: Rectangle {
                            width: 1
                            height: 5
                            color:"white"
                        }

                        background: Rectangle {
                                height: gauge.height+40
                                width: gauge.width+40
                                radius: height/2
                                color: "black"
                                anchors.centerIn: parent
                        }
                    }
                }
                Text{
                    id: vocReadingTextBox
                    width:100
                    height:20
                    anchors.horizontalCenter: gauge.horizontalCenter
                    font.pixelSize: 25
                    text: sensorDisplayString
                }
                Flasher{
                    anchors.horizontalCenter: vocReadingTextBox.horizontalCenter
                    id:flasher
                }
                Text {
                    visible: samplingInProgress
                    anchors.horizontalCenter: gauge.horizontalCenter
                    width: 160
                    height: spinBoxHeight
                    text:VocSensor.stopwatchString
                    font.pixelSize: 36
                    color:"white"
                }


            }

            Column
            {
                spacing:15
                ChartView{
                    width: 450
                    height: 305
                    id: vocReadingChart
                    ValueAxis {
                          id: xAxis
                          min: 0
                          max: xMax
                          tickCount: 5
                          titleText: "Time/s"
                      }
                    LogValueAxis {
                          id: yAxis
                          min: 0.01
                          max: 100
                          //tickCount: 5
                          titleText: "Rs / Ro"
                      }
                Connections{
                    target: VocSensor
                    onNewSample:
                    {
                        flasher.blink()
                        line.append(sampleTime,vocReading)
                        console.log(sampleTime,vocReading)
                        if (sampleTime > xMax)
                            xMax = (xMax*1.5)
                        xAxis.applyNiceNumbers()
                        sensorDisplayString="Rs / Ro: "+vocReading.toFixed(2)
                        if (maxReading<vocReading)
                        {
                            maxReading=vocReading*1.1
//                            yAxis.applyNiceNumbers()
                        }
                    }
                }
                LineSeries{
                    id: line
                    axisX: xAxis
                    axisY: yAxis
//                    XYPoint{x:0;y:1}
                }
            }
                Row{
                    spacing:15
                    Text {
                        width: 100
                        height: spinBoxHeight
                        text: qsTr("Rate / sec:")
                        font.pixelSize: 18
                    }
                    SpinBox {
                        height: spinBoxHeight
                        font.pixelSize: spinBoxTextHeight
                        from: 1
                        to: 120
                        value:1
                        stepSize: 1
                        onValueChanged: {
                            VocSensor.sampleIntervalms=1000*value
                            if (value<10)
                                stepSizeLogarithms=1;
                            else
                                    stepSize=10
                        }
                    }
                    Button{
                        id: saveButton
                        height:30
                        width: 150
                        text: "Save"
                        onClicked: VocSensor.saveData()
                    }

                    Button{
                        height:30
                        width: 60
                        text: "Clear"
                        onClicked:
                        {
                            line.clear()
                            sampleX=0;
                            xMax=10
                            VocSensor.clearSamples()
                        }
                    }
                }
                Row{
                    spacing:30
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button{
                        height:40
                        width: 120
                        text:"Start"
                        onClicked:
                        {
                            VocSensor.startSampling()
                            samplingInProgress=true
                        }
                    }
                    Button{
                        height:40
                        width: 80
                        text:"Stop"
                        onClicked:
                        {
                            VocSensor.stopSampling()
                            samplingInProgress=false
                        }
                    }
                }
            }
        }
    }
}
