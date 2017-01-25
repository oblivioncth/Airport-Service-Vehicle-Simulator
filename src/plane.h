#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsItem>

class Plane : public QGraphicsItem
{
public:
    Plane();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
private:
    qreal angle;
    qreal speed;
    QColor color;
};

#endif
