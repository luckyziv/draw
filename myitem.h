#ifndef MYITEM_H
#define MYITEM_H
#include "common.h"


class MyItem : public QGraphicsItem
{

public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // MYITEM_H
