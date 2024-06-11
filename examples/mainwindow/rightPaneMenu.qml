import QtQuick
import QtQuick.Controls
Rectangle {
    id: root
    color: "transparent"
    ZMenu{
        id: ncFuncMenu
        anchors.fill: parent
        mod: gconf.ncFuncMenus
    }
    Connections{
        target: ncFuncMenu
        function onClickItem(index, name){
            if(index===0){
                rootMain.uiClickNcFunc(index, name);
            }
            else{
                rootMain.uiDisplayUploadProgess();
            }
        }
    }
    Component.onCompleted: function(){
        width = 100
        height = 20 * ncFuncMenu.mod.count
    }
}
