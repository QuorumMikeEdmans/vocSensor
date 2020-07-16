import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtCharts 2.1
import quorum.VocSensor 1.0



CircularGauge {
    id: gauge
    width:220
    height:220
    tickmarksVisible: true
    maximumValue: 3.3
    value: voltage
    stepSize: 1

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
