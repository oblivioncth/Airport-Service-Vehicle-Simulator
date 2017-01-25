#include "plane.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

//MICE SPECIFIC
//-------------
Plane::Plane()
    : angle(0),
      color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setRotation(0);
}

QRectF Plane::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Plane::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Body
    QRectF target(-29, -26, 57, 53);
    QRectF source(0.0, 0.0, 57, 53);
    QImage image(":/ui/Resources/Plane.png");
    painter->drawImage(target, image, source);

    //Center Marker
    painter->setBrush(color);
    painter->drawRect(-2,-2,4,4);
}
