import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

Rectangle{
    id: r
    property var bottomPaneSelectedButtonColor: Qt.rgba(1,1,1,1)
    property var bottomPaneNoSelectButtonColor: Qt.rgba(1,1,1,0.6)
    property string btnClickedBackgroundColor: "#6d829d"
    property var btnDefaultBackgroundColor: Qt.rgba(1,1,1,0.0)
    property bool debug: true
    anchors.fill: parent
    color: "transparent"
    signal sClickBottomMainMenu(int index, int sub);
    signal sClickBottomDetailMenu(int index);

    function updateMainPage(index){
        updateGroupDisplay(groupMainButtons, index);
    }

    function updateDetailPage(index){
        updateGroupDisplay(groupDetailButtons, index);
    }

    function switchJoyOrNC(joy){
        var enabled =  joy ? groupDetailButtons.buttons[8] : groupDetailButtons.buttons[9];
        var disabled =  joy ? groupDetailButtons.buttons[9] : groupDetailButtons.buttons[8];
        setChecked(enabled);
        setUnchecked(disabled);
    }

    function cleanJoyAndNC(){
        console.log("cleanJoyAndNC");
        setUnchecked(groupDetailButtons.buttons[8]);
        setUnchecked(groupDetailButtons.buttons[9]);
    }

    function updateGroupDisplay(btnGroup, index){
        if(btnGroup.buttons.length<=0){
            return;
        }

        if(btnGroup.clickedIndex !== -1){
            setUnchecked(btnGroup.buttons[btnGroup.clickedIndex]);
        }

        btnGroup.clickedIndex = index;
        btnGroup.checkedButton = btnGroup.buttons[index];
        setChecked(btnGroup.buttons[index]);
    }

    function setChecked(btn){
        if(btn && btn.contentItem){
            btn.contentItem.color = r.bottomPaneSelectedButtonColor
        } 
        if(btn && btn.background){
            btn.background.color = r.btnClickedBackgroundColor
        }
    }
    function setUnchecked(btn){
        btn.contentItem.color =  r.bottomPaneNoSelectButtonColor
        btn.background.color = "transparent";
    }

    Rectangle{
        id: rectBottomMenuMain
        x: 0
        y: 0
        color: "transparent"
        width: parent.width
        height: parent.height
        ButtonGroup{
            id: groupMainButtons
            exclusive: true
            property int clickedIndex: -1
            onClicked: function(btn) {
            }
        }
        ListModel {
            id: mainModel
            ListElement {
                name: qsTr("Prod")
                iconsource: "Prod.svg"
            }
            ListElement {
                name: qsTr("Prog")
                iconsource: "Prog.svg"
            }
            ListElement {
                name: qsTr("Tool")
                iconsource: "Tool.svg"
            }
            ListElement {
                name: qsTr("Work")
                iconsource: "Work.svg"
            }
            ListElement {
                name: qsTr("Variable")
                iconsource: "Variable.svg"
            }
            ListElement {
                name: qsTr("Diag")
                iconsource: "Diag.svg"
            }
            ListElement {
                name: qsTr("Service")
                iconsource: "Service.svg"
            }
            ListElement {
                name: qsTr("Extend")
                iconsource: "Extend.svg"
            }
        }

        

        ListView {
            id: rowBottomBtns
            topMargin: 0
            bottomMargin: 0
            leftMargin: 68
            interactive: false
            rightMargin: r.width > 700 ? 68 : 10
            anchors.fill: parent
            orientation: ListView.Horizontal
            model: mainModel
            delegate: RoundButton {
                id: control
                height: parent.height
                ButtonGroup.group: groupMainButtons
                width : (rowBottomBtns.width - rowBottomBtns.leftMargin - rowBottomBtns.rightMargin) / mainModel.count
                radius: 2
                text: name
                font.pixelSize: 10
                icon.source: "%1/%2".arg(gconf.svgPath).arg(iconsource);
                icon.color: "transparent"
                icon.width: 34
                icon.height: 34
                spacing: 0
                display: AbstractButton.TextUnderIcon
                onClicked: {
                    gconf.mainPageIndex = index;
                    sClickBottomMainMenu(index + 1, 0);
                }

                background:  Rectangle {
                    implicitHeight: control.Material.delegateHeight
                    color:  "transparent"
                    Ripple {
                        clip: true
                        clipRadius: parent.radius
                        width: parent.width
                        height: parent.height
                        pressed: control.pressed
                        anchor: control
                        active: enabled && (control.down || control.visualFocus || control.hovered)
                        color: control.flat && control.highlighted ? control.Material.highlightedRippleColor : control.Material.rippleColor
                    }
                    Image{
                        anchors.fill: parent
                        source: "%1/%2".arg(gconf.svgPath).arg("BottomCheckedMenuStyle.svg")
                        visible: gconf.mainPageIndex === index
                    }
                }
                Component.onCompleted: {
                    contentItem.color =  r.bottomPaneNoSelectButtonColor
                }
            }
            Component.onCompleted: {
                //r.updateMainPage(0);
            }
        }
    }
    Rectangle{
        id: rectBottomMenuDetail
        color: "transparent"
        x: parent.x
        y: rectBottomMenuMain.height
        width: parent.width
        height: 0
        ButtonGroup{
            id: groupDetailButtons
            exclusive: false
            property int clickedIndex: -1
        }
        ListModel {
            id: detailModel
            
            Component.onCompleted: {
                clear()
                append({"name": qsTr("Auto"),"iconsource": "Auto"});
                append({"name": qsTr("Single"),"iconsource": "Single"});
                append({"name": qsTr("MDI"),"iconsource": "MDI"});
                append({"name": qsTr("Rapid"),"iconsource": "Rapid"});
                append({"name": qsTr("Search"),"iconsource": "Search"});
                append({"name": qsTr("Test"),"iconsource": "Test"});
                append({"name": qsTr("Manual"),"iconsource": "Manual"});
                append({"name": qsTr("Home"),"iconsource": "Home"});
                append({"name": qsTr("Jog"),"iconsource": "Jog"});
                append({"name": qsTr("NCFunc"),"iconsource": "NCFunc"});
                append({"name": qsTr("Reset"),"iconsource": "Reset"});
            }
        }
        ListView {
            id: rowBottomDetails
            topMargin: 0
            bottomMargin: 0
            interactive: false
            leftMargin: 68/2
            rightMargin: 10
            orientation: ListView.Horizontal
            anchors.fill: parent
            model: detailModel
            delegate: RoundButton {
                id: control2
                height: rowBottomDetails.height
                ButtonGroup.group: groupDetailButtons
                width : (rowBottomDetails.width - rowBottomDetails.leftMargin - rowBottomDetails.rightMargin) / detailModel.count
                radius: 2
                text: name
                font.pixelSize: r.width > 700 ? 10 : 8 //10
                icon.source: "%1/CncMode/%2%3".arg(gconf.svgPath).arg(iconsource).arg(".svg")
                icon.color: "transparent"
                icon.width: 30
                icon.height: 30
                spacing: 0
                display: AbstractButton.TextUnderIcon
                background: Rectangle{
                    color: "transparent"
                    Ripple {
                        clip: true
                        clipRadius: parent.radius
                        width: parent.width
                        height: parent.height
                        pressed: control2.pressed
                        anchor: control2
                        active: enabled && (control2.down || control2.visualFocus || control2.hovered)
                        color: control2.flat && control2.highlighted ? control2.Material.highlightedRippleColor : control2.Material.rippleColor
                    }
                    Image{
                        anchors.fill: parent
                        source: "%1/%2".arg(gconf.svgPath).arg("BottomCheckedMenuStyle.svg")
                        visible: gconf.cncModeIndex === index //groupDetailButtons.clickedIndex === index
                    }
                }
                onClicked: {
                    var pos;
                    sClickBottomDetailMenu(index)
                    if(index === 8){ //joy move
                        pos = control2.mapToItem(bottomRoot, control2.width/2, 0);
                        console.log("9=%1".arg(JSON.stringify(pos)))
                    }
                    else if(index===9){ //nc function
                        pos = control2.mapToItem(bottomRoot, control2.width/2, 0);
                        console.log("9=%1".arg(JSON.stringify(pos)))
                    }
                }
                Component.onCompleted: {
                    contentItem.color =  r.bottomPaneNoSelectButtonColor
                }
            }
            
            Component.onCompleted: {
                if(r.debug){
                    r.updateDetailPage(0);
                }
            }
        }
    }

    AnimationController {
        id: controllerBottom
        property bool toEnd: false
        animation: ParallelAnimation {
            id: pan
            property int timemini : 1000
            NumberAnimation { target: rectBottomMenuMain; property: "height"; duration: pan.timemini; from: r.height; to: 0; easing.type: Easing.InOutQuad }
            NumberAnimation { target: rectBottomMenuDetail; property: "y"; duration: pan.timemini; from: r.height; to: 0; easing.type: Easing.InOutQuad }
            NumberAnimation { target: rectBottomMenuDetail; property: "height"; duration: pan.timemini; from: 0; to: r.height; easing.type: Easing.InOutQuad }
            onFinished: {
                //console.log("animation finished")
            }
        }
        onProgressChanged: function(){
            rectBottomMenuMain.height = (1.0 - progress) * r.height;
            rectBottomMenuDetail.height = progress * r.height;
        }
    }

    function switchBottomMenu(){
        controllerBottom.toEnd = !controllerBottom.toEnd
        if(controllerBottom.toEnd){
            controllerBottom.completeToEnd();
        }
        else{
            controllerBottom.completeToBeginning();
        }
    }
}
