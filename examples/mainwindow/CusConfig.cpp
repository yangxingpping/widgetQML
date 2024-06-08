
#include "CusConfig.h"
#include "magic_enum.hpp"
#include "spdlog/spdlog.h"

CusConfig::CusConfig(QObject *parent) : QObject(parent) 
{
}

CusConfig::~CusConfig() 
{
}

QColor CusConfig::bkColor() 
{
    return _basecolor;
}

void CusConfig::bkColor(QColor color) 
{
    _basecolor = color;
    emit bkColorChanged(_basecolor);
}

QColor CusConfig::hoverColor()
{
    return _hoverColor;
}

void CusConfig::hoverColor(QColor color)
{
    _hoverColor = color;
    emit hoverColorChanged(_hoverColor);
}

QColor CusConfig::popBkColor()
{
    return _popBackgroundColor;
}

void CusConfig::popBkColor(QColor color)
{
    _popBackgroundColor = color;
    emit popBkColorChanged(_popBackgroundColor);
}

QStringList CusConfig::joyMenus()
{
    return _joyMenus;
}

void CusConfig::joyMenus(QStringList menus)
{
    _joyMenus = menus;
    emit joyMenusChanged(_joyMenus);
}

QStringList CusConfig::ncFuncMenus()
{
    return _ncFuncMenus;
}

void CusConfig::ncFuncMenus(QStringList menus)
{
    _ncFuncMenus = menus;
    emit ncFuncMenusChanged(menus);
}

QStringList CusConfig::rightMenus()
{
    return _rightMenus;
}

void CusConfig::rightMenus(QStringList menus)
{
    _rightMenus = menus;
    emit rightMenusChanged(_rightMenus);
}

bool CusConfig::bLoadingPage()
{
    return _bLoaingPage;
}

void CusConfig::bLoadingPage(bool b)
{
    _bLoaingPage = b;
    emit bLoadingPageChanged(_bLoaingPage);
}

QString CusConfig::svgPath()
{
    return _svgPath;
}

void CusConfig::svgPath(QString p)
{
    _svgPath = p;
    emit svgPathChanged(_svgPath);
}

int CusConfig::mainPageIndex()
{
    return magic_enum::enum_integer(_mainPage);
}

void CusConfig::mainPageIndex(int index)
{
    auto optv = magic_enum::enum_cast<PageIndex>(index);
    if(!optv.has_value())
    {
        SPDLOG_WARN("invalid main page value={}", index);
        assert(0);
        return;
    }
    _mainPage = optv.value();
    emit mainPageIndexChanged(index);
}

int CusConfig::cncModeIndex()
{
    return _cncModeIndex;
}

void CusConfig::cncModeIndex(int index)
{
    _cncModeIndex = index;
    emit cncModeIndexChanged(index);
}

int CusConfig::menuItemWidth()
{
    return _menuItemWidth;
}

void CusConfig::menuItemWidth(int w)
{
    _menuItemWidth = w;
    emit menuItemWidthChanged(w);
}

int CusConfig::menuItemHeight()
{
    return _menuItemHeight;
}

void CusConfig::menuItemHeight(int h)
{
    _menuItemHeight = h;
    emit menuItemHeightChanged(h);
}
