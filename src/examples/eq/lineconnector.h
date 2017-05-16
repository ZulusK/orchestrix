#ifndef LINECONNECTOR_H
#define LINECONNECTOR_H

#include <QGraphicsLineItem>

class LineConnector : public QGraphicsLineItem
{

public:

    int xCoordinate1;
    int xCoordinate2;

    int maxYCoordinate1;
    int maxYCoordinate2;


    int currentYCoordinate1;
    int currentYCoordinate2;




    LineConnector(int index, double value1 , double value2);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    QRectF boundingRect() const;


};

#endif // LINECONNECTOR_H
