import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl
import QtQuick.Controls.impl

RoundButton {
    id: control
    radius: 2
    height: 26
    width : 74
    anchors.horizontalCenter: Text.horizontalCenter
    text: "hello"
    property string pmaskUrl: ""
    property color normalBkColor: "green"

    bottomPadding: 2
    topPadding: 2
    leftPadding: 2
    rightPadding: 2
    contentItem: Rectangle{
        id: contentR
        color: "transparent"
        GridLayout{
            anchors.fill: parent
            rowSpacing: 0
            columns: 1// display === AbstractButton.TextBesideIcon ? 2 : 1
            rows: 2// display === AbstractButton.TextUnderIcon ? 2 : 1
            Item{
                width: contentR.width
                height: contentR.height * 3 / 4
                Image{
                    anchors.fill: parent
                    source: control.icon.source
                    sourceSize.width: 100
                    sourceSize.height: 100
                }
            }
            Item{
                width: contentR.width
                height: contentR.height / 4
                Text{
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: control.text
                    font.pixelSize: 16
                }
            }
        }
    }
    background: Rectangle {
        anchors.fill: parent

        radius: 2
        color: control.highlighted ? control.Material.listHighlightColor : (checked ? "yellow" : control.normalBkColor)
        Ripple {
            width: parent.width
            height: parent.height

            clip: visible
            pressed: control.pressed
            anchor: control
            active: control.down || control.visualFocus || control.hovered
            color: control.Material.rippleColor
        }
        Image{
            anchors.fill: parent
            source: control.pmaskUrl;
        }
    }
    font.pixelSize: 10 // mainBottomBasePane.height > 450 ? 10 : 7
    spacing: 0
}
