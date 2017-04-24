#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>


class Equalizer : public QGraphicsItem
{
public:
    Equalizer(int circleIndex , double value , int index);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int xCoordinate;
    int yCoordinate;
    int startY = 0;
    int index = -1;
    int yMax;

protected:
    void advance(int phase);

private:
    qreal speed;
};


#endif // EQUALIZER_H
