import QtQuick
import QtQuick.Controls
import FluentUI
Rectangle {
    id: root
    color: "yellow"
    ListModel{
        id: mod
        ListElement{
            name: qsTr("手轮")
        }
        ListElement{
            text: qsTr("连续给进")
        }
        ListElement {
            text: qsTr("0.001u")
        }
        ListElement {
            text: qsTr("0.01u")
        }
        ListElement {
            text: qsTr("0.1u")
        }
        ListElement {
            text: qsTr("1u")
        }
        ListElement {
            text: qsTr("10u")
        }
        ListElement {
            text: qsTr("100u")
        }
        ListElement {
            text: qsTr("1mm")
        }
        ListElement {
            text: qsTr("10mm")
        }
    }
    ListView{
        anchors.fill: parent
        delegate: Rectangle{
            border.width: 2
            border.color: "blue"
        }
        Component.onCompleted: function(){
            console.log("listview completed width=%1 height=%2".arg(width).arg(height));
        }
        onWidthChanged: function(){
            console.log("list changed width=%1 height=%2".arg(width).arg(height));

        }
    }

    Component.onCompleted: function(){
        console.log("rect completed width=%1 height=%2".arg(width).arg(height));
    }
    onWidthChanged: function(){
        console.log("rect changed width=%1 height=%2".arg(width).arg(height));

    }
}
