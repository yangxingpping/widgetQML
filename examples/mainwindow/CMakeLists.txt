project(QWKExample_MainWindow)

file(GLOB _src *.h *.cpp)

qwk_add_example(${PROJECT_NAME}
    SOURCES ${_src} mainwindow.qrc ../shared/resources/shared.qrc
    QT_LINKS Core Gui Widgets # MultimediaWidgets
    LINKS QWKWidgets WidgetFrame
)


target_link_libraries(QWKExample_MainWindow PRIVATE KF6SyntaxHighlighting PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Qml PRIVATE magic_enum::magic_enum PRIVATE fmt::fmt-header-only PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)