#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>

class Car : public QGraphicsItem
{
public:
    Car();

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
