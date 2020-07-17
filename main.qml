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
    property int x:0
    property real xMax:10
    property int yMax:3
    property string voltageDisplayString
    property real voltage:VocSensor.vocVoltage
    property real maxVoltage:0.5
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
//                Gauge{
//                    id: gauge
//                    width:220
//                    height:220
//                }

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
                    anchors.horizontalCenter: circularGauge.horizontalCenter
                    text: voltageDisplayString
                }

            }

            Column
            {
                ChartView{
                    width: 450
                    height: 350
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
                        line.append(++x,voltage)
                        if (x > xMax)
                            xMax = (xMax*1.5)
                        xAxis.applyNiceNumbers()
                        console.log("New sample", x, xMax, voltage)
                        voltageDisplayString="Voltage: "+voltage.toFixed(2) +"V"
                        if (maxVoltage<voltage)
                            maxVoltage=voltage
                    }
                }
                LineSeries{
                    id: line
                    axisX: xAxis
                    axisY: yAxis
                    XYPoint{x:0;y:0}
                }
            }
                Button{
                    height:50
                    width: 100
                    text: "Save Data"
                }
            }
        }
    }
}
