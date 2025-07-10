#include "line.h"
#include <QPainter>

Line::Line(QPointF point, QObject *parent) :
    Figure(point,parent)
{
    Q_UNUSED(point)
}

Line::~Line()
{

}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));

    QLineF line (startPoint().x() ,
                 startPoint().y() ,
                endPoint().x() ,
                endPoint().y() );

    painter->drawLine(line);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
