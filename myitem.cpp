#include "myitem.h"
#include "math.h"

MyItem::MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                  200000 + penWidth, 200000 + penWidth);
}

index MyItem::get_inflection_point(index p0, index p1, index p2, int instance)
{
    index pp1 = {p1.x - p0.x, p1.y - p0.y};
    index pp2 = {p2.x - p0.x, p2.y - p0.y};
//    qDebug() << "pp1 pp2: " << pp1.x << pp1.y << pp2.x << pp2.y;

    double pp1v = sqrt(pp1.x*pp1.x + pp1.y*pp1.y);
    double pp2v = sqrt(pp2.x*pp2.x + pp2.y*pp2.y);
//    qDebug() << "pp1v pp2v: " << pp1v << pp2v;

    float sin = ((pp1.x*pp2.y - pp2.x*pp1.y) / (pp1v * pp2v));
//    qDebug() << "sin" << sin;

    double pfv = instance / sin;
    double pev = instance / sin;
//    qDebug() << "pfv pev:" << pfv << pev;

    double pec = pev / pp1v;
    index pe = {pec*pp1.x, pec*pp1.y};
//    qDebug() << "pe: " << pe.x << pe.y;

    double pfc = pfv / pp2v;
    index pf = {pfc*pp2.x, pfc*pp2.y};
//    qDebug() << "pf: " << pf.x << pf.y;

    //index pq = {pe.x + pf.x - p0.x, pe.y + pf.y - p0.y};
    index pq = {pe.x + pf.x, pe.y + pf.y};
    qDebug() << "pq: " << pq.x << pq.y;

    return pq;
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black,20, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter->setPen(pen);
    painter->scale(0.05, 0.05);
    painter->setBrush(Qt::red);

#if 1
    // step1. draw border points
    int borderNum = allData.borderPointsNum;

    for (int i = 0, j = 0, k= 0; i < borderNum; i++) {
        ++k;
        if ((i+1) == borderNum)
            k = 0;
        painter->drawLine(QPoint(allData.borderPointsArray[j].x, allData.borderPointsArray[j].y),
                         QPoint(allData.borderPointsArray[k].x, allData.borderPointsArray[k].y));
        j++;
    }

    // step2. draw start points
    QPen pen1(Qt::red, 10, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    painter->setPen(pen1);

    int startNum = allData.startPointsNum;
    for (int i = 0; i < startNum; i++) {
        painter->drawLine(QPoint(allData.startPointsArray[i].pointStartX, allData.startPointsArray[i].pointStartY),
                         QPoint(allData.startPointsArray[i].pointEndX, allData.startPointsArray[i].pointEndY));
    }

    // step3. draw end points
    QPen pen2(Qt::green, 10, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    painter->setPen(pen2);
    int endNum = allData.startPointsNum;
    for (int i = 0; i < endNum; i++) {
        painter->drawLine(QPoint(allData.endPointsArray[i].pointStartX, allData.endPointsArray[i].pointStartY),
                         QPoint(allData.endPointsArray[i].pointEndX, allData.endPointsArray[i].pointEndY));
    }

    // step4. draw inflection points and lines
    int temp = allData.startPointsArray[0].pointStartX;
    int temp1 = 0, idx = 0;
//    qDebug() << "start point: " << temp;
#if 1
    index p0Index, pSIndex, pEIndex;
    for (int i = 0; i < allData.borderPointsNum; i++) {
        temp1 = allData.borderPointsArray[i].x;
//        qDebug() << "for: " << temp1;
        if (temp == allData.borderPointsArray[i].x) {
            if (temp == int(allData.borderPointsArray[i+1].x)) {
                p0Index.x = allData.borderPointsArray[i].x;
                p0Index.y = allData.borderPointsArray[i].y;

                pSIndex.x = allData.borderPointsArray[i+1].x;
                pSIndex.y = allData.borderPointsArray[i+1].y;

                pEIndex.x = allData.borderPointsArray[i-1].x;
                pEIndex.y = allData.borderPointsArray[i-1].y;
                idx = i;
//                qDebug() << "base poing: " << i;
            } else {
                p0Index.x = allData.borderPointsArray[i-1].x;
                p0Index.y = allData.borderPointsArray[i-1].y;

                pSIndex.x = allData.borderPointsArray[i].x;
                pSIndex.y = allData.borderPointsArray[i].y;

                pEIndex.x = allData.borderPointsArray[i-2].x;
                pEIndex.y = allData.borderPointsArray[i-2].y;
                idx = i;
//                qDebug() << "base poing: " << i-1;
            }
            break;
        }
    }

//    qDebug() << "border p0 pS pE" << p0Index.x << p0Index.y << pSIndex.x << pSIndex.y << pEIndex.x << pEIndex.y;

    index p3 = this->get_inflection_point(p0Index, pSIndex, pEIndex,50);
    qDebug() << "1 p0" << p0Index.x << p0Index.y;
    qDebug() << "1 inflection points:" << p3.x << p3.y;
    painter->drawLine(QPoint(-p3.x, allData.startPointsArray[0].pointStartY),
                      QPoint(-p3.x, -p3.y));

    --idx;
    p0Index.x = allData.borderPointsArray[idx].x;
    p0Index.y = allData.borderPointsArray[idx].y;

    pSIndex.x = allData.borderPointsArray[idx+1].x;
    pSIndex.y = allData.borderPointsArray[idx+1].y;

    pEIndex.x = allData.borderPointsArray[idx-1].x;
    pEIndex.y = allData.borderPointsArray[idx-1].y;
    p3 = this->get_inflection_point(p0Index, pSIndex, pEIndex,50);
    qDebug() << "2 p0" << p0Index.x << p0Index.y;
    qDebug() << "2 inflection points" << p3.x << p3.y;
//    painter->drawLine(QPoint(-p3.x, allData.startPointsArray[0].pointStartY),
//                      QPoint(-p3.x, -p3.y));
#endif
#endif

}

