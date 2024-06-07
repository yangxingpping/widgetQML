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

    ButtonGroup{
        id: btnsRight
        exclusive: true
        onClicked: function(btn) {
            console.log('click')
            console.log(btn)
            console.log(checkedButton)
        }
        Component.onCompleted: {

        }
    }
    ListModel {
        id: contactModel
        ListElement{
            name: "first"
        }
        ListElement{
            name: "second"
        }
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
        model: contactModel
        spacing: mainBottomBasePane.height > 450 ? 10 : 5
        delegate: Button {
            height: (rowBottomBtns.height - rowBottomBtns.topMargin - rowBottomBtns.bottomMargin - contactModel.count * rowBottomBtns.spacing) / contactModel.count
            ButtonGroup.group: btnsRight
            width : 74 //parent.width
            anchors.horizontalCenter: Text.horizontalCenter
            text: name
            font.pixelSize: 10 // mainBottomBasePane.height > 450 ? 10 : 7
            spacing: 0
            Component.onCompleted: {
                console.log("button width=%1 height=%2 x=%3 y=%4".arg(width).arg(height).arg(x).arg(y))
            }
            onClicked: {
            }

        }
    }
}
