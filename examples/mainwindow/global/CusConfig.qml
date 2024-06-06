pragma Singleton

import QtQuick
import QtQml.Models
import Qt.labs.qmlmodels

QtObject {
    property int main: 0
    property color backDeepBaseColor : "#375278"
    property color selectedRowColor : "lightgray"
    property var bk : Qt.rgba(backDeepBaseColor.r/255, backDeepBaseColor.g/255, backDeepBaseColor.b/255, 1.0)
    property string svgbasePath: "qrc:/example/res/svg/"
    property string pngbasePath: "qrc:/example/res/image/"
    property string basic_input
    property int bottomPaneHeight: 64
    property int topPaneHeight: 44
    property int rightBottonWidth: 82
    property string form
    property string surface
    property string layout
    property string popus
    property string navigation
    property string theming
    property string media
    property string dark_mode
    property string sys_dark_mode
    property string search
    property string about
    property string settings
    property string locale
    property string navigation_view_display_mode
    property string other
    property string chart
    property string bar_chart
    property string line_chart
    property string pie_chart
    property string polar_area_chart
    property string bubble_chart
    property string scatter_chart
    property string radar_chart
    property int normalTableRowHeigth: 32
    property bool bMock: true

    property string toolsetTipPrefix: qsTr("TOOL SETTINGS")
    property int curToolset: 1
    property int toolsetCount: 255
    property int activeIndex: 0
    property int activeToolSet: 0
    property int toolDirIndex: 0
    property int toolAxisIndex: 0
    property int toolTipIndex: 0
    property string cleanToolOffsetTilps: ""
    property string resetAllOffsetTips: ""
    property string axisInput: "5.0"
    property string nameChe: ""
    property string nameXi: ""

    property string cncName: "cnc"
    property string channelName: "channel"
    property string channelType: "type"

    property int editCncFile: -1
    property string editCncFileName: "demo"
    property string editCncFolderName: "demo"
    property int editDiscOrZone: 0 //0 cnc folder; 1 cnc zone
    property int editFileOrFolder: 0 //0 file; 1 folder
    property bool editIsRoot: true
    property string editData: ""
    property int cncModeIndex: -1
    property int mainPageIndex: 0
    property bool bLoadingPage: true

    property int rightMenuContentWidth: 68 //right menu content width

    //current selected prog file proerties begin
    property string selectedName;
    property string selectedNote;
    property string selectedProgid;
    property bool selectedBhidden;
    property bool selectedBactive;
    //current selected prog file proerties end

    property int selectedJoyIndex: -1;
    property color selectedMenuItemColor: "red"
    property color highLightMenuItemColor: "yellow"

    property string mainTitle: ""
    property string mainTitleSrc: ""



    property string progSkipLevel: "0"
    property var toolSettingModel: ListModel{
        id: secondCol
    }

    property var mainAxisInfoModel: ListModel{
        ListElement{
            imgName: "m5_m"
            titleLabelName: "Spinedle"
            titleName: "Name"
            percent: 0.0
            rpmDesc: ""
            curDesc: ""

            imgName2: "m5_m"
            titleLabelName2: "Spinedle22"
            titleName2: "Name22"
            percent2: 0.0
            rpmDesc2: ""
            curDesc2: ""
        }
    }

    property var cncFolerModel: null;
    property var cncZoneModel: null;

    function clickInRect(pt, rect){
        return pt.x >= rect.x && pt.x <= rect.x + rect.width && pt.y >= rect.y && pt.y <= rect.y + rect.height;
    }

    property var detailModel: ListModel {

    }

    property var prodPosTitle: ListModel{
        ListElement{
            name: ""
        }
        ListElement{
            name: "Pos.OP"
        }
        ListElement{
            name: "Delta"
        }
    }

    property var prodAxisTitle: ListModel{
        ListElement{
            name: ""
        }
        ListElement{
            name: "静态.最大"
        }
        ListElement{
            name: "动态.最大"
        }
        ListElement{
            name: "位置OP"
        }
        ListElement{
            name: "动态.最小"
        }
        ListElement{
            name: "静态.最小"
        }
    }

    property int normalTreeViewHeight: 30
    property int normalTreeViewHeadHeight: 50

    function backBaseColorAlpha(alpha){
        var ret = Qt.rgba(backDeepBaseColor.r/255, backDeepBaseColor.g/255, backDeepBaseColor.b/255, alpha)
        return ret;
    }

   
    Component.onCompleted: {
        for(var i=0; i<8; ++i){
            secondCol.append({
                n0: i,
                type: 0,
                v0: "chedao",
                n1: "L",
                v1: "0.000",
                 n2: "L",
                 v2: "0.000",
                 n3: "L",
                 v3: "0.000",
                 n4: "L",
                 v4: "0.000",
                 n5: "L",
                 v5: "0.000",
                 n6: "L",
                 v6: "0",
                 n7: "L",
                 v7: "0"
            });
        }
    }

}
