#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QDebug>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QByteArray>
#include <QRegExp>
#include <QStringList>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPen>
#include <QPoint>
#include <form.h>

#define startPointsMaxNum   (50)
#define endPointsMaxNum     (50)
#define borderPointsMaxNum  (50)

#define minFlagString       "Min Space:"
#define startFlagString     "Start Teeth:"
#define endFlagString       "End Teeth:"
#define borderFlagString    "Area Polygon:"
#define resFlagString       "Res.constrain:"

typedef struct {
    double x;
    double y;
}borderPointsCoordinate;

typedef struct {
    double pointStartX;
    double pointStartY;

    double pointEndX;
    double pointEndY;
}startPointsCoordinate;

typedef struct {
    double pointStartX;
    double pointStartY;

    double pointEndX;
    double pointEndY;
}endPointsCoordinate;

typedef struct {
    unsigned char startPointsNum;
    unsigned char endPointsNum;
    unsigned char borderPointsNum;

    int lineSpace;

    borderPointsCoordinate borderPointsArray[borderPointsMaxNum];
    startPointsCoordinate startPointsArray[startPointsMaxNum];
    endPointsCoordinate endPointsArray[endPointsMaxNum];
}coordinateData;

#endif // TYPEDEF_H
