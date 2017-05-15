#include "lineconnector.h"
#include <QPainter>

LineConnector::LineConnector(int index, double value1 , double value2)
{
    xCoordinate1 = 10 + index * 40;
    xCoordinate2 = 10 + (index+ 1) * 40;

    maxYCoordinate1 = value1 * 10;
    maxYCoordinate2 = value2 * 10;

    currentYCoordinate1 = 0;
    currentYCoordinate2 = 0;

}

QRectF LineConnector::boundingRect() const
{
    return QRect(0, 0 ,5, 5);
}


void LineConnector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF line(xCoordinate1 , currentYCoordinate1 , xCoordinate2 , currentYCoordinate2);
    painter->setPen(QPen(Qt::blue , 2));
    painter->drawLine(line);
}

void LineConnector::advance(int phase)
{
    if(!phase) return;
    int speed = 5;

    QPointF location1(xCoordinate1 , currentYCoordinate1);
    QPointF location2(xCoordinate2 , currentYCoordinate2);


    if(currentYCoordinate1 >= maxYCoordinate1 && currentYCoordinate2 >= maxYCoordinate2)
    {
        currentYCoordinate1 -= speed;
        currentYCoordinate2 -= speed;
    }

}

