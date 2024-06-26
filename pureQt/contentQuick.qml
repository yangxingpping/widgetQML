// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import pureQt
Item {
    id: root
    
    Component.onCompleted:{
        
    }
    width: 600
    Connections{
        target: abc
        function onSig1(v){
            root.width = v * 5;
        }
    }

    ZRectangle{
        x:0
        y:0
        width: 200
        height: 400
        color: "yellow"
        radius: [5,10,15,20]
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
        text: "Content"
    }
}
