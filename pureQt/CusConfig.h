#pragma once
#include "EPageIndex.h"
#include <QObject>
#include <QQmlEngine>
#include <QColor>
#include <QStringList>
class CusConfig : public QObject {
	Q_OBJECT;
	// QML_SINGLETON
	QML_ELEMENT;
	Q_PROPERTY(QColor backDeepBaseColor READ bkColor NOTIFY bkColorChanged WRITE bkColor);
	Q_PROPERTY(QColor hoverColor READ hoverColor NOTIFY hoverColorChanged WRITE hoverColor);
	Q_PROPERTY(QColor popBkColor READ popBkColor NOTIFY hoverColorChanged WRITE popBkColor);
	Q_PROPERTY(bool bLoaingPage READ bLoadingPage NOTIFY bLoadingPageChanged WRITE bLoadingPage);
	Q_PROPERTY(QString svgPath READ svgPath NOTIFY bLoadingPageChanged WRITE svgPath);
	Q_PROPERTY(int mainPageIndex READ mainPageIndex NOTIFY bLoadingPageChanged WRITE mainPageIndex);
	Q_PROPERTY(int cncModeIndex READ cncModeIndex NOTIFY cncModeIndexChanged WRITE cncModeIndex);

	Q_PROPERTY(int menuItemHeight READ menuItemHeight NOTIFY menuItemHeightChanged WRITE menuItemHeight);
	Q_PROPERTY(int menuItemWidth READ menuItemWidth NOTIFY menuItemWidthChanged WRITE menuItemWidth);

	Q_PROPERTY(QStringList joyMenus READ joyMenus NOTIFY joyMenusChanged WRITE joyMenus);
	Q_PROPERTY(QStringList ncFuncMenus READ ncFuncMenus NOTIFY ncFuncMenusChanged WRITE ncFuncMenus);
	Q_PROPERTY(QStringList rightMenus READ rightMenus NOTIFY rightMenusChanged WRITE rightMenus);
public:
	CusConfig(QObject* parent);
	virtual ~CusConfig();

	QColor bkColor();
	void bkColor(QColor color);

	QColor hoverColor();
	void hoverColor(QColor color);

	QColor popBkColor();
	void popBkColor(QColor color);

	QStringList joyMenus();
	void joyMenus(QStringList menus);

	QStringList ncFuncMenus();
	void ncFuncMenus(QStringList menus);

	QStringList rightMenus();
	void rightMenus(QStringList menus);

	bool bLoadingPage();
	void bLoadingPage(bool b);

	QString svgPath();
	void svgPath(QString p);

	int mainPageIndex();
	void mainPageIndex(int index);

	int cncModeIndex();
	void cncModeIndex(int index);

	int menuItemWidth();
	void menuItemWidth(int w);
	int menuItemHeight();
	void menuItemHeight(int h);
signals:
	void bkColorChanged(const QColor& c);
	void hoverColorChanged(const QColor& c);
	void popBkColorChanged(const QColor& c);
	void bLoadingPageChanged(const bool b);
	void svgPathChanged(const QString& p);
	void mainPageIndexChanged(const int index);
	void cncModeIndexChanged(const int index);
	void joyMenusChanged(QStringList menus);
	void ncFuncMenusChanged(QStringList menus);
	void rightMenusChanged(QStringList menus);

	void menuItemHeightChanged(int h);
	void menuItemWidthChanged(int w);
private:
	QColor _basecolor{ 55, 82, 120 };
	QColor _hoverColor{ 0, 255, 0 };
	QColor _popBackgroundColor{ 0x0f1,0xf3,0xf6 };
	bool _bLoaingPage{ false };
	QString _svgPath{ "qrc:/res/svg" };
	PageIndex _mainPage{ PageIndex::Home };
	int _assistPage{ 0 };
	int _cncModeIndex{ 0 };
	QStringList _joyMenus;
	QStringList _ncFuncMenus;
	QStringList _rightMenus;
	int _menuItemHeight{ 20 };
	int _menuItemWidth{ 120 };
};
