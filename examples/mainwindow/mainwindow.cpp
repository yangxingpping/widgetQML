// Copyright (C) 2023-2024 Stdware Collections (https://www.github.com/stdware)
// Copyright (C) 2021-2023 wangwenx190 (Yuhang Zhao)
// SPDX-License-Identifier: Apache-2.0

#include "mainwindow.h"
#include "codeeditor.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QPushButton>
#include <QQuickWidget>
#include <QQmlContext>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#  include <QtGui/QActionGroup>
#else
#  include <QtWidgets/QActionGroup>
#endif

// #include <QtWebEngineWidgets/QWebEngineView>

#include <QWKWidgets/widgetwindowagent.h>

#include <widgetframe/windowbar.h>
#include <widgetframe/windowbutton.h>

class ClockWidget : public QLabel {
public:
	explicit ClockWidget(QWidget* parent = nullptr) : QLabel(parent) {
		startTimer(100);
		setAlignment(Qt::AlignCenter);
	}

	~ClockWidget() override = default;

protected:
	void timerEvent(QTimerEvent* event) override {
		setText(QTime::currentTime().toString(QStringLiteral("hh:mm:ss")));
	}
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	installWindowAgent();
	gconf = new CusConfig(this);
	// use https://doc.qt.io/qt-6/qtquick-embeddedinwidgets-example.html replace later(performace)
	auto root = new QWidget(this);
	root->setContentsMargins(0, 0, 0, 0);

	popFrame = new Frame(root);
	popFrame->setContextProp(qgconf, gconf);
	popFrame->setContextProp(qrootMain, this);
	setCentralWidget(root);
	{
		topQuick = new QQuickWidget(this);
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
	}
	rootLayout = new QGridLayout(root);
	rootLayout->setContentsMargins(0, 0, 0, 0);
	rootLayout->setRowStretch(0, 0);
	rootLayout->setRowStretch(1, 1);
	rootLayout->setRowStretch(2, 0);
	rootLayout->setColumnStretch(0, 1);
	rootLayout->setColumnStretch(1, 0);

	rootLayout->addWidget(topQuick, 0, 0, 1, 2);
	rootLayout->addWidget(pedit, 1, 0, 1, 1);
	rootLayout->addWidget(rightQuick, 1, 1, 1, 1);
	rootLayout->addWidget(bottomQuick, 2, 0, 1, 2);

#ifdef Q_OS_WIN
	QWidget* pp = new QWidget(this);
	pp->setMinimumHeight(30);
	rootLayout->addWidget(pp, 3, 0, 1, 2);
#endif
	rootLayout->setSpacing(1);

	loadStyleSheet(Light);

	uiGoProdHome();

	resize(1024, 768);
}

static inline void emulateLeaveEvent(QWidget* widget) {
	Q_ASSERT(widget);
	if (!widget) {
		return;
	}
	QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
		const QScreen* screen = widget->screen();
#else
		const QScreen* screen = widget->windowHandle()->screen();
#endif
		const QPoint globalPos = QCursor::pos(screen);
		if (!QRect(widget->mapToGlobal(QPoint{ 0, 0 }), widget->size()).contains(globalPos)) {
			QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
			if (widget->testAttribute(Qt::WA_Hover)) {
				const QPoint localPos = widget->mapFromGlobal(globalPos);
				const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
				static constexpr const auto oldPos = QPoint{};
				const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 4, 0))
				const auto event =
					new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
				Q_UNUSED(localPos);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
				const auto event = new QHoverEvent(QEvent::HoverLeave, localPos, globalPos, oldPos, modifiers);
				Q_UNUSED(scenePos);
#else
				const auto event = new QHoverEvent(QEvent::HoverLeave, localPos, oldPos, modifiers);
				Q_UNUSED(scenePos);
#endif
				QCoreApplication::postEvent(widget, event);
			}
		}
		});
}

MainWindow::~MainWindow() = default;

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
	popFrame->resize(120, lst.size() * 20);
	popFrame->setSource(QUrl("qrc:/ncJoyMenu.qml"));
	auto rPos = mapToGlobal(bottomQuick->geometry().topLeft());
	popFrame->move(rPos.x() + pt.x(), rPos.y() - lst.size() * 20 + bottomQuick->geometry().height());
	popFrame->show();
}

void MainWindow::uiClickJoyFunc(int index, QString name)
{
	popFrame->hide();
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
	popFrame->move(rPos.x() - 120, rPos.y() + pt.y() + topQuick->geometry().height());
	popFrame->show();
}

bool MainWindow::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::WindowActivate:
	{
		auto menu = menuWidget();
		if (menu) {
			menu->setProperty("bar-active", true);
			style()->polish(menu);
		}
		break;
	}
	case QEvent::WindowDeactivate:
	{
		auto menu = menuWidget();
		if (menu) {
			menu->setProperty("bar-active", false);
			style()->polish(menu);
		}
		break;
	}

	default:
		break;
	}
	return QMainWindow::event(event);
}


void MainWindow::closeEvent(QCloseEvent* event) {
	// if (!(qApp->keyboardModifiers() & Qt::ControlModifier)) {
	//     QTimer::singleShot(1000, this, &QWidget::show);
	// }
	event->accept();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	if (!isMaximized()) // forbidden resize by move mouse
	{
		resize(1024, 768);
		event->ignore();
		return;
	}
	QMainWindow::resizeEvent(event);
}

void MainWindow::installWindowAgent() {
	// 1. Setup window agent
	windowAgent = new QWK::WidgetWindowAgent(this);
	windowAgent->setup(this);

	// 2. Construct your title bar
	auto menuBar = [this]() {
		auto menuBar = new QMenuBar();
		menuBar->setLayoutDirection(Qt::RightToLeft);
		// Virtual menu
		auto file = new QMenu(tr("A1"), menuBar);

		auto edit = new QMenu(tr("A2"), menuBar);

		// Theme action
		auto darkAction = new QAction(tr("Enable dark theme"), menuBar);
		darkAction->setCheckable(true);
		connect(darkAction, &QAction::triggered, this, [this](bool checked) {
			loadStyleSheet(checked ? Dark : Light); //
			});
		connect(this, &MainWindow::themeChanged, darkAction, [this, darkAction]() {
			darkAction->setChecked(currentTheme == Dark); //
			});

#ifdef Q_OS_WIN
		auto dwmBlurAction = new QAction(tr("Enable DWM blur"), menuBar);
		dwmBlurAction->setCheckable(true);
		connect(dwmBlurAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("dwm-blur"), checked)) {
				return;
			}
			setProperty("custom-style", checked);
			style()->polish(this);
			});

		auto acrylicAction = new QAction(tr("Enable acrylic material"), menuBar);
		acrylicAction->setCheckable(true);
		connect(acrylicAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("acrylic-material"), true)) {
				return;
			}
			setProperty("custom-style", checked);
			style()->polish(this);
			});

		auto micaAction = new QAction(tr("Enable mica"), menuBar);
		micaAction->setCheckable(true);
		connect(micaAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("mica"), checked)) {
				return;
			}
			setProperty("custom-style", checked);
			style()->polish(this);
			});

		auto micaAltAction = new QAction(tr("Enable mica alt"), menuBar);
		micaAltAction->setCheckable(true);
		connect(micaAltAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("mica-alt"), checked)) {
				return;
			}
			setProperty("custom-style", checked);
			style()->polish(this);
			});
#elif defined(Q_OS_MAC)
		auto darkBlurAction = new QAction(tr("Dark blur"), menuBar);
		darkBlurAction->setCheckable(true);
		connect(darkBlurAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "dark")) {
				return;
			}
			if (checked) {
				setProperty("custom-style", true);
				style()->polish(this);
			}
			});

		auto lightBlurAction = new QAction(tr("Light blur"), menuBar);
		lightBlurAction->setCheckable(true);
		connect(lightBlurAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "light")) {
				return;
			}
			if (checked) {
				setProperty("custom-style", true);
				style()->polish(this);
			}
			});

		auto noBlurAction = new QAction(tr("No blur"), menuBar);
		noBlurAction->setCheckable(true);
		connect(noBlurAction, &QAction::toggled, this, [this](bool checked) {
			if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "none")) {
				return;
			}
			if (checked) {
				setProperty("custom-style", false);
				style()->polish(this);
			}
			});

		auto macStyleGroup = new QActionGroup(menuBar);
		macStyleGroup->addAction(darkBlurAction);
		macStyleGroup->addAction(lightBlurAction);
		macStyleGroup->addAction(noBlurAction);
#endif

		// Real menu
		auto settings = new QMenu(tr("S1"), menuBar);


#ifdef Q_OS_WIN
#elif defined(Q_OS_MAC)
		settings->addAction(darkBlurAction);
		settings->addAction(lightBlurAction);
		settings->addAction(noBlurAction);
#endif
		auto settingss = new QMenu(tr("S2"), menuBar);
		menuBar->addMenu(file);
		menuBar->addMenu(edit);
		menuBar->addMenu(settings);
		menuBar->addMenu(settingss);

		return menuBar;
		}();
	menuBar->setObjectName(QStringLiteral("win-menu-bar"));

	auto titleLabel = new QLabel();
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setObjectName(QStringLiteral("win-title-label"));

#ifndef Q_OS_MAC
	auto iconButton = new QWK::WindowButton();
	iconButton->setObjectName(QStringLiteral("icon-button"));
	iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	auto minButton = new QWK::WindowButton();
	minButton->setObjectName(QStringLiteral("min-button"));
	minButton->setProperty("system-button", true);
	minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	auto maxButton = new QWK::WindowButton();
	maxButton->setCheckable(true);
	maxButton->setObjectName(QStringLiteral("max-button"));
	maxButton->setProperty("system-button", true);
	maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	auto closeButton = new QWK::WindowButton();
	closeButton->setObjectName(QStringLiteral("close-button"));
	closeButton->setProperty("system-button", true);
	closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

	auto windowBar = new QWK::WindowBar();
	// windowBar->setFixedHeight(24);
#ifndef Q_OS_MAC
	// windowBar->setIconButton(iconButton);
	windowBar->setMinButton(minButton);
	windowBar->setMaxButton(maxButton);
	windowBar->setCloseButton(closeButton);
#endif
	// windowBar->setMenuBar(menuBar);
	windowBar->setTitleLabel(titleLabel);
	windowBar->setHostWidget(this);

	windowAgent->setTitleBar(windowBar);
#ifndef Q_OS_MAC
	// windowAgent->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
	windowAgent->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
	windowAgent->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
	windowAgent->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
#endif
	windowAgent->setHitTestVisible(menuBar, true);

#ifdef Q_OS_MAC
	windowAgent->setSystemButtonAreaCallback([](const QSize& size) {
		static constexpr const int width = 75;
		return QRect(QPoint(size.width() - width, 0), QSize(width, size.height())); //
		});
#endif

	setMenuWidget(windowBar);


#ifndef Q_OS_MAC
	connect(windowBar, &QWK::WindowBar::minimizeRequested, this, &QWidget::showMinimized);
	connect(windowBar, &QWK::WindowBar::maximizeRequested, this, [this, maxButton](bool max) {
		if (max) {
			showMaximized();
		}
		else {
			showNormal();
		}

		// It's a Qt issue that if a QAbstractButton::clicked triggers a window's maximization,
		// the button remains to be hovered until the mouse move. As a result, we need to
		// manually send leave events to the button.
		emulateLeaveEvent(maxButton);
		});
	connect(windowBar, &QWK::WindowBar::closeRequested, this, &QWidget::close);
#endif
}

void MainWindow::loadStyleSheet(Theme theme) {
	if (!styleSheet().isEmpty() && theme == currentTheme)
		return;
	currentTheme = theme;

	if (QFile qss(theme == Dark ? QStringLiteral(":/dark-style.qss")
		: QStringLiteral(":/light-style.qss"));
		qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
		setStyleSheet(QString::fromUtf8(qss.readAll()));
		Q_EMIT themeChanged();
	}
}
