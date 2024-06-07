
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
