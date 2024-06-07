import QtQuick
import QtQuick.Controls

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
            radius: 6
            height: (rowBottomBtns.height - rowBottomBtns.topMargin - rowBottomBtns.bottomMargin - gconf.rightMenus.length * rowBottomBtns.spacing) / gconf.rightMenus.length
            width : 74 //parent.width
            anchors.horizontalCenter: Text.horizontalCenter



            font.pixelSize: 10 // mainBottomBasePane.height > 450 ? 10 : 7
            spacing: 0
            onClicked: {
            }

        }
    }
}
