#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //painter = new QPainter(this);
    //painter->scale(10, 10);

    qDebug() << "Form";
}


Form::~Form()
{
    delete ui;
}

void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::black, 500, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter.setPen(pen);
    painter.scale(0.003, 0.003);    // must float

    int borderNum = allData.borderPointsNum;

    for (int i = 0, j = 0, k= 0; i < borderNum; i++) {
        ++k;

        if ((i+1) == borderNum)
            k = 0;
        painter.drawLine(QPoint(allData.borderPointsArray[j].x, allData.borderPointsArray[j].y),
                         QPoint(allData.borderPointsArray[k].x, allData.borderPointsArray[k].y));
        j++;

    }


    //painter.drawLine(QPoint(10000, 10000), QPoint(200000, 200000));

    qDebug() << "paintEvent";
}
