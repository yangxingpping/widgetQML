// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: root
    
    Component.onCompleted:{
        
        console.log("width:%1 height:%2".arg(width).arg(height))
        
    }
    width: 600
    Connections{
        target: abc
        function onSig1(v){
            console.log("pass para=%1".arg(v));
            root.width = v * 5;
        }
    }
    
    Rectangle{
        id: hehe
        //anchors.fill: parent
        
        x: 0
        y: 0
        width: root.width
        height: 400
        color: "red"
    }
    Text {
        id: text
        anchors.centerIn: parent
        property string api
        Connections {
            target: text.GraphicsInfo
            function onApiChanged() {
                var api = text.GraphicsInfo.api;
                if (api === GraphicsInfo.Software)
                    text.api = "Software";
                else if (api === GraphicsInfo.OpenGL)
                    text.api = "OpenGL on QRhi";
                else if (api === GraphicsInfo.Direct3D11)
                    text.api = "D3D11 on QRhi";
                else if (api === GraphicsInfo.Direct3D12)
                    text.api = "D3D12 on QRhi";
                else if (api === GraphicsInfo.Vulkan)
                    text.api = "Vulkan on QRhi";
                else if (api === GraphicsInfo.Metal)
                    text.api = "Metal on QRhi";
                else if (api === GraphicsInfo.Null)
                    text.api = "Null on QRhi";
                else
                    text.api = "Unknown API";
            }
        }
        text: "Qt Quick running in a widget\nGraphicsInfo.api says: " + api
    }
}
