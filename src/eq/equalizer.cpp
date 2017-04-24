#include "equalizer.h"
#include <QDebug>

Equalizer::Equalizer(int circleIndex , double value , int index)
{
    speed = 5;
    this->index = index;
    int xCoordinate = 10 + circleIndex * 40;
    int yCoordinate = value * 10;

    yMax = -yCoordinate;
    setPos(mapToParent(xCoordinate , startY));

}

QRectF Equalizer::boundingRect() const
{
    return QRect(0, 0 ,5, 5);
}

void Equalizer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::red);
    painter->fillRect(rec , brush);
    painter->drawEllipse(rec);
}

void Equalizer::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();
    qDebug() << "CURRENT Y POS : " << location.y();

    if(location.y() <= yMax)
    {
        return;
    }


    setPos(mapToParent(0 , -(speed)));
 }
