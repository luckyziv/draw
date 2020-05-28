#include "myitem.h"

myItem::myItem()
{

}

QRectF myItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void myItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 500, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter->setPen(pen);
    painter->scale(0.003, 0.003);
    painter->setBrush(Qt::red);
//    painter->drawRect(0, 0, 30, 30);
    QLine line(0, 0, 500000.0, 500000.0);
//    QLine line(10.0, 10.0, 15.0, 15.0);
    painter->drawLine(line);

#if 0

    int borderNum = allData.borderPointsNum;

    for (int i = 0, j = 0, k= 0; i < borderNum; i++) {
        ++k;

        if ((i+1) == borderNum)
            k = 0;
        painter->drawLine(QPoint(allData.borderPointsArray[j].x, allData.borderPointsArray[j].y),
                         QPoint(allData.borderPointsArray[k].x, allData.borderPointsArray[k].y));
        j++;

    }
#endif

}

