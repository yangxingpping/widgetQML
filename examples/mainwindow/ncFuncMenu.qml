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
            name: qsTr("连续给进")
        }
        ListElement {
            name: qsTr("0.001u")
        }
        ListElement {
            name: qsTr("0.01u")
        }
        ListElement {
            name: qsTr("0.1u")
        }
        ListElement {
            name: qsTr("1u")
        }
        ListElement {
            name: qsTr("10u")
        }
        ListElement {
            name: qsTr("100u")
        }
        ListElement {
            name: qsTr("1mm")
        }
        ListElement {
            name: qsTr("10mm")
        }
        Component.onCompleted: function(){
            console.log("menu count=%1".arg(count));
        }
    }
    ListView{
        anchors.fill: parent
        model: mod
        interactive: false
        delegate: Rectangle{
            height: parent.height / mod.count
            width: parent.width
            border.width: 1
            border.color: "blue"
            Text {
                anchors.centerIn: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: name
            }
            MouseArea{
                anchors.fill: parent
                onClicked: function(){
                    console.log("clicked");
                }
            }
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
