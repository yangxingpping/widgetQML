import QtQuick
import QtQuick.Controls
Rectangle {
    id: root
    ZMenu{
        id: joyMenu
        anchors.fill: parent
        mod: ListModel{
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
        }
        Connections{
            target: joyMenu
            function onClickItem(index, name){
                rootMain.uiClickJoyFunc(index, name);
            }
        }
    }
}
