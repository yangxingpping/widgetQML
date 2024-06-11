import QtQuick
import QtQuick.Controls
Rectangle {
    id: root
    //color: "yellow"
    ZMenu{
        id: joyMenu
        anchors.fill: parent
        mod: gconf.joyMenus
        Connections{
            target: joyMenu
            function onClickItem(index, name){
                rootMain.uiClickJoyFunc(index, name);
            }
        }
    }
}
