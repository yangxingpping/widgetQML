import QtQuick
import QtQuick.Controls

Row{
    id: r
    anchors.fill: parent
    spacing: 1
    property var buttons: null
    property int btnWidth: 74
    property int btnHeigth: 26
    Repeater{
        model: r.buttons
        ZButton{
            display: AbstractButton.TextUnderIcon
            palette.buttonText: "red"
            radius: r.btnRadius
            width: r.btnWidth
            height: r.btnHeigth
            text: name
            pmaskUrl: maskUrl
            icon.source: iconUrl
            icon.color: "transparent"
            Component.onCompleted: function(){
                console.log("model data=%1".arg(iconUrl))
            }
        }
    }
}

