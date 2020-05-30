#ifndef MYITEM_H
#define MYITEM_H
#include "common.h"


class MyItem : public QGraphicsItem
{
public:
    int borderNum_g;
    index get_inflection_point(index p0, index p1, index p2, int instance);
    void paint_line(QPainter *painter);
public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // MYITEM_H
