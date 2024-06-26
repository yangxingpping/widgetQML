cmake_minimum_required(VERSION 3.27)

project(pureQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Qml QuickWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Qml QuickWidgets)

qt6_add_resources(Z_RESOURCES_TARGET demo.qrc)

aux_source_directory(./ A)
set(UIS
    mainwindow.ui
    mainwindow.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pureQt
        MANUAL_FINALIZATION
        ${A}
        ${UIS}
        ${Z_RESOURCES_TARGET}
        #demo.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET pureQt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(pureQt SHARED
        ${A}
        ${UIS}
        ${Z_RESOURCES_TARGET}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(pureQt
        ${A}
        ${UIS}
        ${Z_RESOURCES_TARGET}
        )
    endif()
endif()

qt_add_qml_module(pureQt
    URI pureQt
    VERSION 1.0
    #QML_FILES Main.qml
    SOURCES ZRectangle.cpp ZRectangle.h
)

target_link_libraries(pureQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Qml PRIVATE KF6SyntaxHighlighting PRIVATE magic_enum::magic_enum PRIVATE fmt::fmt-header-only PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.pureQt)
endif()
set_target_properties(pureQt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS pureQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pureQt)
endif()
