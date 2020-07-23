import QtQuick 2.0

Rectangle{
    id: flasher
    property bool flash: false
    property int flashTime: 300
    signal blink()
    property color ledColor: "green"
    Timer{
        id: timeFlash
        interval: flashTime
        repeat: false
        onTriggered: flash=false
    }

    width:16
    height:width
    radius:width/2
    border.width: 1
    border.color: "dark grey"
    onBlink:
    {
        flash=true
        timeFlash.start()
    }
    Rectangle
    {
        anchors.centerIn: parent
        width:parent.width-4
        height:width
        radius:width/2
        color: parent.flash ? ledColor:"#c0c0c0"
    }

}
