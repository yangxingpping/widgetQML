
#include "CusConfig.h"

CusConfig::CusConfig(QObject *parent) : QObject(parent) {
}

CusConfig::~CusConfig() {
}

QColor CusConfig::bkColor() {
    return _basecolor;
}

void CusConfig::bkColor(QColor color) {
    _basecolor = color;
    emit bkColorChanged(_basecolor);
}
