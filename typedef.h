#ifndef TYPEDEF_H
#define TYPEDEF_H


#define startPointsMaxNum   (50)
#define endPointsMaxNum     (50)
#define borderPointsMaxNum  (50)

#define minFlagString       ("Min Space")
#define startFlagString     ("Start Teeth")
#define endFlagString       ("End Teeth")
#define borderFlagString    ("Area Polygon")
#define resFlagString       ("Res.constrain")
#define miniWidth           ("Min Width")

typedef struct {
    double x;
    double y;
}index;

typedef struct {
    double x;
    double y;
}borderPointsCoordinate;

typedef struct {
    double pointStartX;
    double pointStartY;

    double pointEndX;
    double pointEndY;
}PointsCoordinate;

typedef struct {
    unsigned char startPointsNum;
    unsigned char endPointsNum;
    unsigned char borderPointsNum;

    float sheetRatio;
    float minWidth;
    float minSpace;

    borderPointsCoordinate borderPointsArray[borderPointsMaxNum];
    PointsCoordinate startPointsArray[startPointsMaxNum];
    PointsCoordinate endPointsArray[endPointsMaxNum];
}coordinateData;

extern coordinateData allData;

#endif // TYPEDEF_H
