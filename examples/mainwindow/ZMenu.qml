import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    anchors.fill: parent
    property var mod: null;
    border.width: 2
    border.color: "lightgray"
    ListView{
        anchors.centerIn: parnet
        x: parent.border.width
        y: parent.border.width
        width: parent.width - 2 * parent.border.width
        height: parent.height - 2 * parent.border.width
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
