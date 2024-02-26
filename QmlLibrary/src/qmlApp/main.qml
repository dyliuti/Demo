import QtQuick 2.15
import QtQuick.Window 2.15
import YmwPlugin 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ComText {
        anchors.left: parent.left
        anchors.top: parent.top
        text: "nihao"
    }
//Text {
//    anchors.left: parent.left
//    anchors.top: parent.top
//    text: "nihao"
//}

    DateTimeItem {
        anchors.right: parent.right
        anchors.top: parent.top
        width: 200
        height: 200
    }


}
