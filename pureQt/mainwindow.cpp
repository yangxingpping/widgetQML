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
	rootLayout->setRowStretch(0, 0);
	rootLayout->setRowStretch(1, 1);
	rootLayout->setRowStretch(2, 0);

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

	rootLayout->addWidget(_pTopBar, 0, 0);

    this->resize(1024, 768);

    _pTopBar->updateRunState("Running", QColor{ 0,255,255 }, QColor{ 255,0,0 });

}

MainWindow::~MainWindow()
{
    delete ui;
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

