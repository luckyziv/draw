#ifndef MYITEM_H
#define MYITEM_H
#include "common.h"


class MyItem : public QGraphicsItem
{
public:

    index get_inflection_point(index p0, index p1, index p2, int instance);
public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // MYITEM_H
