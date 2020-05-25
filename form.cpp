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
//    QPainterPath paintPath;

    painter.setPen(pen);
    painter.scale(0.003, 0.003);    // must float

    painter.drawLine(QPoint(10000, 10000), QPoint(200000, 200000));

//    paintPath.moveTo(10000, 10000);
//    paintPath.lineTo(100000, 100000);

//    painter.drawPath(paintPath);
    qDebug() << "paintEvent";
}
