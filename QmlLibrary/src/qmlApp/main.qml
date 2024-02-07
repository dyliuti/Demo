import QtQuick 2.15
import QtQuick.Window 2.15
import YmwPlugin 1.0

Window {
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
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
}
