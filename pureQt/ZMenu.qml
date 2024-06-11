import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    anchors.fill: parent
    property var mod: null;
    color: "transparent" // "blue"
    border.width: 2
    border.color: "lightgray"
    signal clickItem(int index, string name);
    ListView{
        anchors.centerIn: parent
        width: parent.width - 2 * parent.border.width
        height: parent.height - 2 * parent.border.width
        model: mod
        interactive: false
        delegate: Rectangle{
            id: del
            height: root.height / mod.length
            width: parent.width
            color: "transparent" //gconf.popBkColor
            Rectangle{
                id: rectHover
                anchors.fill: parent
                color: gconf.backDeepBaseColor
                opacity: 0.3
                visible: false
            }

            Text {
                anchors.centerIn: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: modelData
                color: gconf.backDeepBaseColor
            }
            MouseArea{
                anchors.fill: parent
                onClicked: function(){
                    clickItem(index, modelData)
                }
                hoverEnabled: true
                onEntered: {
                    rectHover.visible = true;
                }
                onExited: function(){
                    rectHover.visible = false;
                }
            }
        }

    }


}
