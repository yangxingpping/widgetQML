import QtQuick

Item {
    id: root
    
    Component.onCompleted:{
        
        console.log("width:%1 height:%2".arg(width).arg(height))
        
    }
    width: 86
    Rectangle{
        anchors.fill: parent
        color: gconf.backDeepBaseColor
        opacity: 0.3
    }
}
