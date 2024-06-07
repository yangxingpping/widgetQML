project(QWKExample_MainWindow)

file(GLOB _src *.h *.cpp)

set(qml_singletons
    global/CusConfig.qml
    global/Lang.qml
)

qwk_add_example(${PROJECT_NAME}
    SOURCES ${_src} mainwindow.qrc ../shared/resources/shared.qrc ${qml_singletons}
    QT_LINKS Core Gui Widgets # MultimediaWidgets
    LINKS QWKWidgets WidgetFrame
)


target_link_libraries(QWKExample_MainWindow PRIVATE KF6SyntaxHighlighting PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Qml PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)