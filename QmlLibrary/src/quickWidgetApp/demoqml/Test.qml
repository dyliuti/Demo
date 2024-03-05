import QtQuick 2.12
import QtQuick.Controls 2.12

import YmwPlugin 1.0

Rectangle {
    id: root
    color: "#262626"
    ComText {
        anchors.left: parent.left
        anchors.top: parent.top
        text: "nihao"
        color: "black"
    }

//    Image {
//        anchors.fill: parent
//        source: "file:///C:/background.png"
//        sourceSize.width: 2560
//        sourceSize.height: 1440
//    }

//    ImageItem {
//        anchors.fill: parent
//    }

//        DateTimeItem {
//            width: 200
//            height: 200
//            anchors.right: parent.right
//            anchors.top: parent.top
//        }


    Timer {
        interval: 1000
        running: true
        onTriggered: {
            timeTxt.text = getClockText()
        }
    }

    Text {
        id: timeTxt
        width: 200
        height: 200
        anchors.right: parent.right
        anchors.top: parent.top
        text: getClockText()
        color: "blue"
    }

    function getClockText(){
        let date = new Date()
        let hours = date.getHours()
        let minutes = date.getMinutes()
        if(minutes < 10){
            minutes = "0" + minutes
        }

        return hours + ":" + minutes
    }


    MyItem {
        width: 200
        height: 200
        anchors.left: parent.left
    }

    ComImage {

    }
}
