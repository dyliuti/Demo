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
    }

    MyItem {
        width: 200
        height: 200
        anchors.left: parent.left
    }

    ComImage {

    }
}
