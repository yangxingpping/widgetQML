#include "mainwindow.h"
#include "zmousepresspane.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QWindow>
#include <QLabel>
#include <QFrame>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _pTopBar = new ZTopBar(this);
    _pTopBar->setStyleSheet("QFrame { background-color : rgba(55,82,120, 0.2) }");
	auto root = new QWidget(this);
	root->setContentsMargins(0, 0, 0, 0);

	setCentralWidget(root);

	rootLayout = new QGridLayout(root);
	rootLayout->setContentsMargins(0, 0, 0, 0);

    QObject::connect(_pTopBar, &ZTopBar::startMainWindowMove, this, &MainWindow::onStartSystemMove, Qt::QueuedConnection);

    QObject::connect(_pTopBar, &ZTopBar::closeWindow, this, [this]() {
        this->close();
        }, Qt::QueuedConnection);
    QObject::connect(_pTopBar, &ZTopBar::minimizeWindow, this, [this]() {
        this->showMinimized();
        }, Qt::QueuedConnection);
    QObject::connect(_pTopBar, &ZTopBar::maximizeWindow, this, [this]() {
        if(this->isMaximized())
        {
            this->showNormal();
        }
        else 
        {
            this->showMaximized();
        }
        emit _pTopBar->mainWindowMaxmized(this->isMaximized());
     }, Qt::QueuedConnection);


    //add content
	gconf = new CusConfig(this);
	// use https://doc.qt.io/qt-6/qtquick-embeddedinwidgets-example.html replace later(performace)
	root->setContentsMargins(0, 0, 0, 0);

	popFrame = new Frame(root);
	popFrame->setContextProp(qgconf, gconf);
	popFrame->setContextProp(qrootMain, this);
	setCentralWidget(root);
	{
		topQuick = new QQuickWidget(this);
		topQuick->setContentsMargins(0, 0, 0, 0);
		topQuick->rootContext()->setContextProperty(qgconf, gconf);
		QUrl source1("qrc:/topQuick.qml");
		topQuick->setSource(source1);
		topQuick->setResizeMode(QQuickWidget::SizeRootObjectToView);
		topQuick->setMinimumHeight(44);
	}

	{
		rightQuick = new QQuickWidget(this);
		rightQuick->rootContext()->setContextProperty(qgconf, gconf);
		rightQuick->rootContext()->setContextProperty(qrootMain, this);
		QUrl source1("qrc:/rightQuick.qml");
		rightQuick->setSource(source1);
		rightQuick->setResizeMode(QQuickWidget::SizeRootObjectToView);
		rightQuick->setMinimumWidth(86);
	}

	{
		bottomQuick = new QQuickWidget(this);
		bottomQuick->rootContext()->setContextProperty(qgconf, gconf);
		bottomQuick->rootContext()->setContextProperty(qrootMain, this);
		QUrl source1("qrc:/bottomQuick.qml");
		bottomQuick->setSource(source1);
		bottomQuick->setResizeMode(QQuickWidget::SizeRootObjectToView);
		bottomQuick->setMinimumHeight(62);
	}

	contentQuick = new QQuickWidget(this);
	pedit = new CodeEditor(this);
	pedit->setVisible(true);
	contentQuick->rootContext()->setContextProperty("abc", pedit);

	{
		QUrl source("qrc:/contentQuick.qml");
		contentQuick->rootContext()->setContextProperty(qgconf, gconf);
		contentQuick->setSource(source);
		contentQuick->setResizeMode(QQuickWidget::SizeRootObjectToView);
		contentQuick->setVisible(false);
	}

	rootLayout->setRowStretch(0, 0);
	rootLayout->setRowStretch(1, 0);
	rootLayout->setRowStretch(2, 1);
	rootLayout->setRowStretch(3, 0);
	rootLayout->setColumnStretch(0, 1);
	rootLayout->setColumnStretch(1, 0);

	rootLayout->addWidget(_pTopBar, 0, 0, 1, 2);

	rootLayout->addWidget(topQuick, 1, 0, 1, 2);
	rootLayout->addWidget(pedit, 2, 0, 1, 1);
	rootLayout->addWidget(contentQuick, 2, 0, 1, 1);
	rootLayout->addWidget(rightQuick, 2, 1, 1, 1);
	rootLayout->addWidget(bottomQuick, 3, 0, 1, 2);
	rootLayout->setSpacing(1);
    //end content
	this->resize(1024, 768);

    _pTopBar->updateRunState("Running", QColor{ 0,255,255 }, QColor{ 255,0,0 });
	uiGoProdHome();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayNCFunc(QPoint pt)
{
	QStringList lst{ "M01", "跳段", "设置程序段跳过级别" };
	gconf->ncFuncMenus(lst);
	popFrame->resize(120, lst.size() * 20);
	popFrame->setSource(QUrl("qrc:/ncFuncMenu.qml"));
	auto rPos = mapToGlobal(bottomQuick->geometry().topLeft());
	popFrame->move(rPos.x() + pt.x(), rPos.y() - lst.size() * 20 + bottomQuick->geometry().height());
	popFrame->show();
}

void MainWindow::uiClickNcFunc(int index, QString name)
{
	popFrame->hide();
}

void MainWindow::displayJoyFunc(QPoint pt)
{
	QStringList lst{ "手轮", "连续给进", "0.001u", "0.01u", "0.1u", "1u", "10u", "100u", "1mm", "10mm" };
	gconf->joyMenus(lst);
	int mwidth = gconf->menuItemWidth();
	int mheight = gconf->menuItemHeight();
	popFrame->resize(mwidth, lst.size() * mheight);
	popFrame->setSource(QUrl("qrc:/ncJoyMenu.qml"));
	auto rPos = mapToGlobal(bottomQuick->geometry().topLeft());

	popFrame->move(rPos.x() + pt.x(), rPos.y() - lst.size() * mheight + bottomQuick->geometry().height());

	popFrame->show();
}

void MainWindow::uiClickJoyFunc(int index, QString name)
{
	popFrame->hide();
}

void MainWindow::uiDisplayUploadProgess()
{

}

void MainWindow::uiGoProdHome()
{
	QStringList lst{ "手轮", "连续给进", "0.001u", "0.01u", "0.1u", "1u", "10u", "100u", "1mm", "10mm" };
	gconf->rightMenus(lst);
}

void MainWindow::uiDisplayRightMenuSub(int index, QPoint pt)
{
	QStringList lst{ "手轮", "连续给进", "0.001u", "0.01u", "0.1u", "1u", "10u", "100u", "1mm", "10mm" };
	gconf->ncFuncMenus(lst);
	popFrame->resize(120, lst.size() * 20);
	popFrame->setSource(QUrl("qrc:/rightPaneMenu.qml"));
	auto rPos = mapToGlobal(rightQuick->geometry().topLeft());
	popFrame->move(rPos.x() - 120, rPos.y() + pt.y());// +topQuick->geometry().height());
	popFrame->show();
}


void	MainWindow::mousePressEvent(QMouseEvent *e)
{
    //qDebug() << "pressed";
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug() << "released";
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    //qDebug() << "moved";
    //this->windowHandle()->startSystemMove();
}

void MainWindow::onStartSystemMove()
{
    this->windowHandle()->startSystemMove();
}

void MainWindow::showEvent(QShowEvent* event)
{
    emit _pTopBar->mainWindowMaxmized(this->isMaximized());
}

