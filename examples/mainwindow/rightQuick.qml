import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Rectangle {
    id: root
    width: 86
    Rectangle{
        anchors.fill: parent
        color: gconf.backDeepBaseColor
        opacity: 0.3
    }
    ListView {
        id: rowBottomBtns
        topMargin: parent.height > 450 ? 15 : 0
        bottomMargin: parent.height > 450 ? 15 : 0
        leftMargin: 7
        rightMargin: 7
        interactive: false
        anchors.centerIn: parent
        width: parent.width
        height: parent.height // - 64
        orientation: ListView.Vertical
        model: gconf.rightMenus
        spacing: root.height > 450 ? 10 : 5
        delegate: RoundButton {
            id: control
            radius: 6
            height: (rowBottomBtns.height - rowBottomBtns.topMargin - rowBottomBtns.bottomMargin - gconf.rightMenus.length * rowBottomBtns.spacing) / gconf.rightMenus.length
            width : 74 //parent.width
            anchors.horizontalCenter: Text.horizontalCenter
            text: modelData
            contentItem: Text {
                text: control.text
                font: control.font
                opacity: enabled ? 1.0 : 0.3
                color: gconf.backDeepBaseColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                anchors.fill: parent
                //implicitHeight: control.Material.delegateHeight
                radius: 6
                color: control.highlighted ? control.Material.listHighlightColor : (checked ? "yellow" : "white")
                //color: "0xffffff"
                Ripple {
                    width: parent.width
                    height: parent.height

                    clip: visible
                    pressed: control.pressed
                    anchor: control
                    active: control.down || control.visualFocus || control.hovered
                    color: control.Material.rippleColor
                }
            }

            font.pixelSize: 10 // mainBottomBasePane.height > 450 ? 10 : 7
            spacing: 0
            onClicked: {
                var pos = control.mapToItem(root, 0, 0);
                rootMain.uiDisplayRightMenuSub(index, pos);
            }
        }
    }
}
