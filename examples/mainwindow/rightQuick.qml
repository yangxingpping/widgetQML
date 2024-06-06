import QtQuick
import "./global"
Item {
    id: root
    
    Component.onCompleted:{
        
        console.log("width:%1 height:%2".arg(width).arg(height))
        
    }
    width: 86
    Rectangle{
        anchors.fill: parent
        color: "#375278"
        opacity: 0.3
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
                    text.api = "right";
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
        text: "Right"
    }
}
