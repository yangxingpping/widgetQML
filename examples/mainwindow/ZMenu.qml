import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    anchors.fill: parent
    color: "yellow"
    property var mod: ListModel{
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
            id: del
            height: root.height / mod.count
            width: parent.width

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
                hoverEnabled: true
                onEntered: {
                    del.color = "red"
                    del.border.color = "white"
                    del.border.width = 3
                }
                onExited: function(){
                    del.color = "white"
                    del.border.width=0;
                }
            }
        }

    }


}
