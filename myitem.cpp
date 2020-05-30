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
    qDebug() << "before add :" <<pe.x + pf.x << pe.y + pf.y;
    index pq = {pe.x + pf.x - p0.x, pe.y + pf.y - p0.y};
//    index pq = {pe.x + pf.x, pe.y + pf.y};
//    qDebug() << "pq: " << pq.x << pq.y;

    return pq;
}


void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black,20, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter->setPen(pen);
    painter->scale(0.05, 0.05);
    painter->setBrush(Qt::red);

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
    index p0Index, pSIndex, pEIndex;
    borderNum_g = 0;
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
//                idx = i + 2;
                idx = i;
                borderNum_g = i + 2;
                qDebug() << "base poing: " << i;
            } else {
                p0Index.x = allData.borderPointsArray[i-1].x;
                p0Index.y = allData.borderPointsArray[i-1].y;

                pSIndex.x = allData.borderPointsArray[i].x;
                pSIndex.y = allData.borderPointsArray[i].y;

                pEIndex.x = allData.borderPointsArray[i-2].x;
                pEIndex.y = allData.borderPointsArray[i-2].y;
                idx = i;
                borderNum_g = i + 1;
//                qDebug() << "base poing: " << i-1;
            }
            break;
        }
    }
    this->paint_line(painter);
#if 0
//    qDebug() << "border p0 pS pE" << p0Index.x << p0Index.y << pSIndex.x << pSIndex.y << pEIndex.x << pEIndex.y;

    index p3 = this->get_inflection_point(p0Index, pSIndex, pEIndex,50);
    qDebug() << "1 rural points" << p0Index.x << p0Index.y;
    qDebug() << "1 inflection points:" << p3.x << p3.y;
    painter->drawLine(QPoint(-p3.x, allData.startPointsArray[0].pointStartY),
                      QPoint(-p3.x, -p3.y));
    index last = {-p3.x, -p3.y};

    --idx;
    p0Index.x = allData.borderPointsArray[idx].x;
    p0Index.y = allData.borderPointsArray[idx].y;

    pSIndex.x = allData.borderPointsArray[idx+1].x;
    pSIndex.y = allData.borderPointsArray[idx+1].y;

    pEIndex.x = allData.borderPointsArray[idx-1].x;
    pEIndex.y = allData.borderPointsArray[idx-1].y;
    p3 = this->get_inflection_point(p0Index, pSIndex, pEIndex,50);
    qDebug() << "2 rural points" << p0Index.x << p0Index.y;
    qDebug() << "2 inflection points" << p3.x << p3.y;
    painter->drawLine(QPoint(last.x, last.y),
                      QPoint(-p3.x, -p3.y));

    for(int i=0; i<allData.startPointsNum; i++) {


    }
#endif
}

void MyItem::paint_line(QPainter *painter)
{
    index pS, p0, pE, pb, pq;

    index borderRecord[borderNum_g];
    qDebug() << "borderNum_g: " << borderNum_g;
    for(int i = 0; i < borderNum_g; i++) {
        borderRecord[i].x = allData.borderPointsArray[i].x;
        borderRecord[i].y = allData.borderPointsArray[i].y;
        qDebug() << "borderRecord data:" << borderRecord[i].x << borderRecord[i].y;
    }

    index startRecord[allData.startPointsNum];
    for(int i = 0; i < allData.startPointsNum; i++) {
        startRecord[i].x = allData.startPointsArray[i].pointStartX;
        startRecord[i].y = allData.startPointsArray[i].pointStartY;
    }

    index endRecord[allData.endPointsNum];
    for(int i = 0; i < allData.endPointsNum; i++) {
        endRecord[i].x = allData.endPointsArray[i].pointStartX;
        endRecord[i].y = allData.endPointsArray[i].pointStartY;
    }

    int k = 0;
    for (int i = 0; i < allData.startPointsNum; i++) {
        if ( i == 0) {
            pb.x = startRecord[i].x + 50;
            pb.y = startRecord[i].y;
        } else {
            pb.x = startRecord[i].x;
            pb.y = startRecord[i].y;
        }
        ++k;
        for (int i = (borderNum_g - 2), j = 0; i >= 0; i--) {
            j = i;
            p0.x = borderRecord[j].x;
            p0.y = borderRecord[j].y;
            pS.x = borderRecord[j+1].x;
            pS.y = borderRecord[j+1].y;
            pE.x = borderRecord[j-1].x;
            pE.y = borderRecord[j-1].y;

            index p3 = this->get_inflection_point(p0, pS, pE,50);


            if (i == 0) {
                // connect end points
                painter->drawLine(QPoint(pb.x, pb.y),
                                  QPoint(endRecord[k-1].x, endRecord[k-1].y));

            } else {
                painter->drawLine(QPoint(pb.x, pb.y),
                                  QPoint(-p3.x, -p3.y));
            }

            if (j == (borderNum_g - 2)) {
                borderRecord[j+1].x = pb.x;
                borderRecord[j+1].y = pb.y;
                borderRecord[j].x = -p3.x;
                borderRecord[j].y = -p3.y;
            } else {
                borderRecord[j].x = -p3.x;
                borderRecord[j].y = -p3.y;
            }
            pb.x = -p3.x;
            pb.y = -p3.y;
        }
    }
}
