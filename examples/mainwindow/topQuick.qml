// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
//import "./global"

Item {
    id: root
    
    Component.onCompleted:{
        
        console.log("width:%1 height:%2".arg(width).arg(height))
        
    }
    width: 600
    MainTopPane{
        id: hehe
        
        anchors.fill: parent
        
        //color: gconf.backDeepBaseColor
        //opacity: 0.1
    }
    
}
