#ifndef ZRectangle_H
#define ZRectangle_H


#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QColor>

#include "zstdafx.h"

/**
 * @brief The ZRectangle class
 */
class ZRectangle : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY_AUTO(QColor,color)
    Q_PROPERTY_AUTO(QList<int>,radius)
    QML_NAMED_ELEMENT(ZRectangle)
public:
    explicit ZRectangle(QQuickItem *parent = nullptr);
    void paint(QPainter* painter) override;
};

#endif // ZRectangle_H
