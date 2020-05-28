#ifndef MYITEM_H
#define MYITEM_H
#include "common.h"
#include "typedef.h"


class myItem : public QGraphicsItem
{

public:
    myItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // MYITEM_H
