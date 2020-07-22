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
    property real xMax:10
    property int yMax:3
    property string voltageDisplayString
    property real voltage:VocSensor.vocVoltage
    property real maxVoltage:0.5
    property int spinBoxHeight: 40
    property int spinBoxTextHeight:24
    title: qsTr("VOC Sensor monitor")

    Rectangle{
        anchors.fill: parent
        z:99
//        color: "light blue"
        gradient: Gradient {
            GradientStop {position: 0; color: "#7FA4EF"}
            GradientStop {position: 0.5; color: "#4F81BD"}
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
                    maximumValue: 3.3
                    value: voltage
                    stepSize: 0.05

                    style: CircularGaugeStyle{
                        tickmarkStepSize: 0.5
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
                    width:100
                    height:20
                    anchors.horizontalCenter: gauge.horizontalCenter
                    font.pixelSize: 15
                    text: voltageDisplayString
                }

            }

            Column
            {
                spacing:15
                ChartView{
                    width: 450
                    height: 305
                    id: voltageChart
                    ValueAxis {
                          id: xAxis
                          min: 0
                          max: xMax
                          tickCount: 5
                          titleText: "Samples"
                      }
                    ValueAxis {
                          id: yAxis
                          min: 0
                          max: maxVoltage
                          tickCount: 5
                          titleText: "Volts"
                      }
                Connections{
                    target: VocSensor
                    onNewSample:
                    {
                        line.append(++sampleX,voltage)
                        if (sampleX > xMax)
                            xMax = (xMax*1.5)
                        xAxis.applyNiceNumbers()
                        console.log("New sample", sampleX, xMax, voltage)
                        voltageDisplayString="Voltage: "+voltage.toFixed(2) +"V"
                        if (maxVoltage<voltage)
                        {
                            maxVoltage=voltage*1.1
                            yAxis.applyNiceNumbers()
                        }
                    }
                }
                LineSeries{
                    id: line
                    axisX: xAxis
                    axisY: yAxis
                    XYPoint{x:0;y:0}
                }
            }
                Row{
                    spacing:15
                    Text {
                        width: 160
                        height: spinBoxHeight
                        text: qsTr("Sample interval/ sec:")
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
                                stepSize=1;
                            else
                                    stepSize=10
                        }
                    }
                    Button{
                        height:30
                        width: 40
                        text: "Save"
                        onClicked: VocSensor.saveData()
                    }
                    Button{
                        height:30
                        width: 40
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
                        text:"Start Sampling"
                        onClicked: VocSensor.startSampling()
                    }
                    Button{
                        height:40
                        width: 80
                        text:"Stop"
                        onClicked: VocSensor.stopSampling()
                    }
                }
            }
        }
    }
}
