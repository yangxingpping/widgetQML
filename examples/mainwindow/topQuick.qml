import QtQuick
import QtQuick.Shapes 1.5

Rectangle {
    id: r
    color: "transparent"
    MainTopPane{
        id: hehe
        anchors.fill: parent
        visible: false
    }
    property int width1: 123
    property int width2: 145
    property int sepwidth: 5
    Shape {
        ShapePath {
            id: mainTopLeftRealPanel
            fillColor: "#e4e8ed"
            strokeWidth: 2
            strokeColor: "#e4e8ed"
            startX: 0; startY: 0
            PathSvg {
                id: mainTopLeftRealPanelPath
                path: "L %1 0 L %2 %3 L 0 %3 z".arg(r.width - r.width1 - r.sepwidth).arg(r.width - r.width2 - r.sepwidth).arg(r.height)
            }
        }
    }

    Shape {
        ShapePath {
            id: mainTopRightRealPanel
            fillColor: "#e4e8ed"
            strokeWidth: 2
            strokeColor: "#e4e8ed"
            startX: r.width - r.width1
            startY: 0
            PathSvg {
                id: mainTopRightRealPanelPath
                path: "L %1 0 L %1 %2 L %3 %2 z".arg(r.width).arg(r.height).arg(r.width - r.width2)
            }
        }
    }
}
