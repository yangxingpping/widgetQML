#pragma once
#include <QObject>
#include <QQmlEngine>
#include <QColor>
class CusConfig : public QObject
{
	Q_OBJECT
		QML_SINGLETON
		QML_ELEMENT
	
	Q_PROPERTY(QColor backDeepBaseColor READ bkColor WRITE bkColor USER true)
public:
	CusConfig(QObject* parent);
	virtual ~CusConfig();
	QColor bkColor();
	void bkColor(QColor color);
	QColor _basecolor{ 255,0,0 };
};

