#include "myitem.h"


MyItem::MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                  200000 + penWidth, 200000 + penWidth);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 100, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter->setPen(pen);
    painter->scale(0.05, 0.05);
    painter->setBrush(Qt::red);
#if 1
//    painter->drawRect(0, 0, 30, 30);
//    QLine line(0, 0, 50000.0, 50000.0);
////    QLine line(10.0, 10.0, 15.0, 15.0);
//    painter->drawLine(line);
#endif

#if 1

    int borderNum = allData.borderPointsNum;

    for (int i = 0, j = 0, k= 0; i < borderNum; i++) {
        ++k;
        if ((i+1) == borderNum)
            k = 0;
//        qDebug() << allData.borderPointsArray[j].x << allData.borderPointsArray[j].y;
//        qDebug() << allData.borderPointsArray[k].x << allData.borderPointsArray[k].y;
        painter->drawLine(QPoint(allData.borderPointsArray[j].x, allData.borderPointsArray[j].y),
                         QPoint(allData.borderPointsArray[k].x, allData.borderPointsArray[k].y));
        j++;
    }

    int startNum = allData.startPointsNum;
    for (int i = 0; i < startNum; i++) {
        painter->drawLine(QPoint(allData.startPointsArray[i].pointStartX, allData.startPointsArray[i].pointStartY),
                         QPoint(allData.startPointsArray[i].pointEndX, allData.startPointsArray[i].pointEndY));
    }

    int endNum = allData.startPointsNum;
    for (int i = 0; i < endNum; i++) {
        painter->drawLine(QPoint(allData.endPointsArray[i].pointStartX, allData.endPointsArray[i].pointStartY),
                         QPoint(allData.endPointsArray[i].pointEndX, allData.endPointsArray[i].pointEndY));
    }
#endif

}

