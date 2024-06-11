#pragma once
#include "magic_enum.hpp"
#include "ZTwoDimension.h"
#include <QLocale>
#include <QtQml>
#include <memory>
#include <map>
#include <vector>

using std::map;
using std::unique_ptr;
using std::vector;



ZTwoDimension::ZTwoDimension(QObject* parent)
	:QAbstractListModel(parent)
{

}
ZTwoDimension::~ZTwoDimension()
{
}
int ZTwoDimension::rowCount(const QModelIndex& index) const
{
	return zrowCount(index);
}
QVariant ZTwoDimension::data(const QModelIndex& index, int role) const
{
	return zdata(index, role);
}
QHash<int, QByteArray> ZTwoDimension::roleNames() const
{
	return _roles;
}

QVariant ZTwoDimension::zdata(const QModelIndex& index, int role) const
{
	assert(0);
	return QVariant();
}

int ZTwoDimension::zrowCount(const QModelIndex& index) const
{
	assert(0);
	return 0;
}
