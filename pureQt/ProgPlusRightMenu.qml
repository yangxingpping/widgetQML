import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import FluentUI 1.0
import "../global"
import "../component"

Rectangle{
    id: mainBottomBasePane
    anchors.fill: parent
    color: "transparent"
    Rectangle{
        anchors.fill: parent
        color: CusConfig.backDeepBaseColor
        opacity: 0.3
    }
    z: 10036
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
    }
    signal sEditFile()
    signal sDelFile()
    signal sGetFileProp()

    FluContentDialog{
        id:dlg_del_file
        width: 330
        height: 226
        title: qsTr("你想删除选中的文件吗")
        //message:"数据正在加载中，请稍等..."
        contentDelegate: Component{
            Item{
                implicitWidth: parent.width
                implicitHeight: 80
                Label{

                    width: 482
                    height: 30
                    anchors.centerIn: parent
                    text: CusConfig.editCncFileName
                    onTextChanged: {
                        let a = parseInt(text)
                        if(a>0){
                            dlg_d_num.goToPage = parseInt(text)
                        }
                    }
                }
            }
        }
        negativeText: qsTr("否")
        onNegativeClicked:{
            showSuccess("点击取消按钮")
        }
        positiveText: qsTr("是")
        onPositiveClicked:{
            mainBottomBasePane.sDelFile()
            //r.goToPage(dlg_d_num.goToPage)
            showSuccess("点击确定按钮")
        }
    }

    ProgPlusRightSubMenuFunction{
        id: functionMenu
    }

    FluContentDialog{
        id:dlgProgFileProp
        width: 596
        height: 300
        title: qsTr("文件属性")
        message: ""
        property string inputTitle: "输入数值"
        property string progSkipLevel: CusConfig.progSkipLevel
        onOpened: function(){
            cncfolder.getCncFileProp(CusConfig.editCncFile);
            sUpdateFileProp(CusConfig.selectedName, CusConfig.selectedNote, CusConfig.selectedProgid, CusConfig.selectedBhidden, CusConfig.selectedBactive);
        }

        signal sUpdateFileProp(string name, string note, string progid, bool bhidden, bool bactive);

        contentDelegate: Component{
            Rectangle{
                id: rectSkipLevelContent
                implicitWidth: parent.width
                implicitHeight: 200
                Connections{
                    target: dlgProgFileProp
                    function onSUpdateFileProp(name, note, progid, hidden, active){
                        txtName.text = name;
                        txtNote.text = note;
                        txtProg.text = progid
                        txtHidden.checked = hidden
                        txtActive.checked = active
                    }
                }

                Rectangle{
                    id: rectSkipText
                    anchors.centerIn: parent
                    width: parent.width - 50
                    height: parent.height - 50
                    Grid{
                        anchors.fill: parent
                        columnSpacing: 5
                        rowSpacing: 5
                        columns: 2
                        Label{
                            id: lbName
                            width: parent.width / 3
                            height: parent.height / 5
                            text: "文件名"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        TextField{
                            id: txtName
                            text: "名称"
                            width: parent.width * 2 / 3
                            height: parent.height / 5
                            verticalAlignment: Text.AlignVCenter
                            enabled: false
                            color: CusConfig.backDeepBaseColor
                        }
                        Label{
                            id: lbNote
                            width: parent.width / 3
                            height: parent.height / 5
                            text: "备注"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        TextField{
                            id: txtNote
                            width: parent.width * 2 / 3
                            height: parent.height / 5
                            text: "note"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        Label{
                            id: lbProg
                            width: parent.width / 3
                            height: parent.height / 5
                            text: "程序号码"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        TextField{
                            id: txtProg
                            width: parent.width * 2 / 3
                            height: parent.height / 5
                            text: "prog"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        Label{
                            id: lbhidden
                            width: parent.width / 3
                            height: parent.height / 5
                            text: "文件保护"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        MyCheckBox{
                            id: txtHidden
                            width: parent.width * 2 / 3
                            height: parent.height / 5
                            text: "隐藏"
                            bkColor: CusConfig.backDeepBaseColor

                        }
                        Label{
                            id: lbactive
                            width: parent.width / 3
                            height: parent.height / 5
                            text: "主程序"
                            verticalAlignment: Text.AlignVCenter
                            color: CusConfig.backDeepBaseColor
                        }
                        MyCheckBox{
                            id: txtActive
                            width: parent.width * 2 / 3
                            height: parent.height / 5
                            text: "激活"
                            bkColor: CusConfig.backDeepBaseColor

                        }
                    }
                }
            }
        }
        positiveText: qsTr("Yes")
        onPositiveClicked:{
            //showSuccess("点击确定按钮")
            pagemain.setSkipLevel(dlgSetProgSkipLevel.progSkipLevel);
        }
        onNegativeClicked: {

        }
    }

    Connections{
        target: cncfolder
        function onSuccGetCncFileProp(folder, note, name, hidden, active){
            CusConfig.selectedName = folder;
            CusConfig.selectedNote = note;
            CusConfig.selectedProgid = name;
            CusConfig.selectedBhidden = hidden;
            CusConfig.selectedBactive = active;
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
        delegate: FluButton {
            height: (rowBottomBtns.height - rowBottomBtns.topMargin - rowBottomBtns.bottomMargin - contactModel.count * rowBottomBtns.spacing) / contactModel.count
            ButtonGroup.group: btnsRight
            width : 74 //parent.width
            anchors.horizontalCenter: Text.horizontalCenter
            text: name
            textColor: CusConfig.backDeepBaseColor
            font.pixelSize: 10 // mainBottomBasePane.height > 450 ? 10 : 7
            spacing: 0
            Component.onCompleted: {
                console.log("button width=%1 height=%2 x=%3 y=%4".arg(width).arg(height).arg(x).arg(y))
            }
            onClicked: {
                if(index===0){
                    functionMenu.width = 256
                    functionMenu.x = -functionMenu.width    
                    functionMenu.open()
                }
                else if(index===1){ //get file property

                    dlgProgFileProp.open();
                    //sGetFileProp();
                }

                else if(index===2){ //delete code
                    dlg_del_file.open();
                }

                else if(index===3){ //edit code
                    sEditFile();
                }
            }

        }
    }
    function addMenu(menus){
        contactModel.clear()
        for(var i = 0; i<menus.length; ++i){
            contactModel.append({"name": menus[i]})
        }
        console.log(menus)
    }
    Component.onCompleted: {
        //dlgProgFileProp.open();
        console.log("mainBottomBasePane hegith %1".arg(mainBottomBasePane.height))
    }
}
