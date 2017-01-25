#include "car.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

//MICE SPECIFIC
//-------------
Car::Car()
    : angle(0),
      color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setRotation(0);
}

QRectF Car::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Car::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    painter->setBrush(color);
    painter->drawRect(-6, -10, 12, 20);

    //Front Lights
    painter->setBrush(Qt::yellow);
    painter->drawRect(2,-10,4,4);
    painter->drawRect(-6,-10,4,4);

    //Rear Light
    painter->setBrush(Qt::red);
    painter->drawRect(-3,8,6,2);

    //Center Marker
    painter->setBrush(Qt::red);
    painter->drawRect(0,0,1,1);
}
