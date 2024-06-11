import QtQuick
import QtQuick.Controls
Rectangle {
    id: root
    ZMenu{
        id: ncFuncMenu
        anchors.fill: parent
        mod: gconf.ncFuncMenus
    }
    Connections{
        target: ncFuncMenu
        function onClickItem(index, name){
            rootMain.uiClickNcFunc(index, name);
        }
    }
    Component.onCompleted: function(){
        width = 100
        height = 20 * ncFuncMenu.mod.count
    }
}
