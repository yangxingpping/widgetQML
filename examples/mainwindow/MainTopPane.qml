import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Shapes 1.5

Rectangle {
    id: rootBackground
    color: "transparent" //CusConfig.backDeepBaseColor
    anchors.fill: parent
    Rectangle{
        id: mainTopLeftPane
        anchors{
            top: title.bottom
            left: parent.left
        }
        width: parent.width * 0.874
        height: parent.height
        //color: "yellow"
        Component.onCompleted: {
            console.debug("main top left width %1, heigth %2".arg(width).arg(height));
        }
        Shape {
            ShapePath {
                id: mainTopLeftRealPanel
                fillColor: "#e4e8ed"
                //opacity: 0.8
                strokeWidth: 2
                strokeColor: "#e4e8ed"
                startX: 0; startY: 0
                PathSvg { 
                    id: mainTopLeftRealPanelPath
                    path: "L 400 0 L 400 %1 L 0 %1 z".arg(mainTopLeftPane.height) 
                }
            }

        }
    }

    Rectangle{
        id: mainTopRightPane
        anchors{
            right: parent.right
            top: title.bottom
        }
        height: parent.height
        width: parent.width - mainTopLeftPane.width - 4
        //color: "black"
        Shape {
            ShapePath {
                id: mainTopRightRealPanel
                fillColor: "#e4e8ed"
                //opacity: 0.8
                strokeWidth: 2
                strokeColor: "#e4e8ed"
                startX: 4; startY: 0
                PathSvg { 
                    id: mainTopRightRealPanelPath
                    path: "L 400 0 L 400 %1 L -14 %1 z".arg(mainTopRightPane.height) 
                }
            }

        }
    }
    onWidthChanged: {
        console.log("main top pane width changed");
        var curpath = "L %1 0 L %1 62 L 0 62 z"
        console.log(curpath.arg(rootBackground.width))

        mainTopLeftPane.width = rootBackground.width * 0.874
        curpath = "L %1 0 L %2 %3 L 0 %3 z"
        mainTopLeftRealPanelPath.path = curpath.arg(mainTopLeftPane.width).arg(mainTopLeftPane.width - 18).arg(mainTopLeftPane.height)

        mainTopRightPane.width = rootBackground.width - mainTopLeftPane.width - 4
        curpath = "L %1 0 L %2 44 L %3 44 z"
        //console.log("main top left width %1, heigth %2, mainTopLeftPane width %3 after root width changed".arg(width).arg(height).arg(mainTopLeftPane.width));
    }
}
