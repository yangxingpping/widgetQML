import QtQuick
import QtQuick.Controls

Column{
    id: r
    anchors.fill: parent
    spacing: 5
    property var buttons: ["ok", "cancel"]
    property int btnWidth: 74
    property int btnHeigth: 26
    property int btnRadius: 6
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
        }
    }
}

