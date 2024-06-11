#include "ztopbar.h"

ZTopBar::ZTopBar(QWidget *parent)
    : QFrame{parent}
{
    setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(_height);
    _rootLayout = new QGridLayout(this);
    _rootLayout->setContentsMargins(2, 0, 22, 0);
    _rootLayout->setSpacing(10);

    _leftTitle = new QLabel(_rootLayout->widget());
    _leftTitle->setText("Hello");
    _leftTitle->setFixedWidth(100);
    _rootLayout->addWidget(_leftTitle, 0, 0);

    _movePane = new ZMousePressPane(this->windowHandle(), _rootLayout->widget());
    _movePane->setStyleSheet("QWidget { background-color : transparent }");

    _rootLayout->addWidget(_movePane, 0, 1);

    _btnMini = new QPushButton(_rootLayout->widget());
    _btnMini->setFixedWidth(_height);
    {
        QIcon qIcon;
        qIcon.addFile(":/res/res/minimize_top_icon.svg", QSize(64, 64), QIcon::Normal, QIcon::On);
        _btnMini->setIcon(qIcon);
    }
    QObject::connect(_btnMini, &QPushButton::clicked, this, &ZTopBar::minimizeWindow, Qt::QueuedConnection);
    _rootLayout->addWidget(_btnMini, 0, 2);


    _btnMax = new QPushButton(_rootLayout->widget());
    QObject::connect(this, &ZTopBar::mainWindowMaxmized, this, [this](bool bMax) {
        QString postfix = bMax ? "2" : "";
        QString iconPath = QString::fromStdString(":/res/res/amplification_top_icon%1.svg").arg(postfix);
		QIcon qIcon;
		qIcon.addFile(iconPath, QSize(64, 64), QIcon::Normal, QIcon::On);
		_btnMax->setIcon(qIcon);
        //_btnMax->setStyleSheet("QPushButton { background-color : transparent }");
        }, Qt::QueuedConnection);
    
    _btnMax->setFixedWidth(_height);
    QObject::connect(_btnMax, &QPushButton::clicked, this, &ZTopBar::maximizeWindow, Qt::QueuedConnection);
    _rootLayout->addWidget(_btnMax, 0, 3);

    _btnClose = new QPushButton(_rootLayout->widget());
	{
		QIcon qIcon;
		qIcon.addFile(":/res/res/close_top_icon.svg", QSize(64, 64), QIcon::Normal, QIcon::On);
        _btnClose->setIcon(qIcon);
	}
    QObject::connect(_btnClose, &QPushButton::clicked, this, &ZTopBar::closeWindow, Qt::QueuedConnection);
    _btnClose->setFixedWidth(_height);
    _rootLayout->addWidget(_btnClose, 0, 4);

    //_btnMini->setStyleSheet("QPushButton { background-color : transparent }");
    //_btnClose->setStyleSheet("QPushButton { background-color : transparent }");
    _btnMini->setFixedHeight(_height);
    _btnMax->setFixedHeight(_height);
    _btnClose->setFixedHeight(_height);

    QObject::connect(_movePane, &ZMousePressPane::startMainWindowMove, this, &ZTopBar::startMainWindowMove, Qt::QueuedConnection);
}

ZTopBar::~ZTopBar()
{

}

void ZTopBar::updateRunState(QString text, QColor backcolor, QColor forgecolor)
{
    QString style = QString::fromStdString("QLabel { background-color : %1; color : %2; }").arg(backcolor.name()).arg(forgecolor.name());
    _leftTitle->setStyleSheet(style);
    _leftTitle->setText(text);
}

void ZTopBar::showEvent(QShowEvent* event)
{
    
}
