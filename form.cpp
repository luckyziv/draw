#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //painter = new QPainter(this);
    //painter->scale(10, 10);
    m_scale = 1;
    resize(1200,800);
    sceneWidget = new QWidget(this);
    sceneWidget->setStyleSheet("border:none; background:blue;");

    sceneWidget->setFixedSize(800,800);
    view = new QGraphicsView(sceneWidget);
    view->setStyleSheet("border:none; background:lightgray;");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene(sceneWidget);
//    scene->setSceneRect(0,0,800,600);
    view->setScene(scene);
//    view->setSceneRect(0,0,800,600);

//    m_bkPixmapItem = new QGraphicsPixmapItem();
//    m_bkPixmapItem->setPixmap(QPixmap(":/new/prefix1/src/3.png").scaled(280,60,Qt::KeepAspectRatioByExpanding));
//    scene->addItem(m_bkPixmapItem);
    scene->addItem(&item);

    view->resize(800,800);
    view->scene()->setSceneRect(0,0,800,600);
    this->setCentralWidget(sceneWidget);
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

void Form::wheelEvent(QWheelEvent *event)
{
    view->scale(1/m_scale, 1/m_scale);
    if(event->delta() > 0){
        if(m_scale < 10){
            m_scale += 0.1;
        }else{
            m_scale = 10;
        }
    }else{
        if(m_scale > 0.1){
            m_scale -= 0.1;
        }else{
            m_scale = 0.1;
        }
    }
    view->scale(m_scale, m_scale);
    qDebug()<<m_scale;
}

void Form::mousePressEvent(QMouseEvent *event)
{
    m_lastPointF = event->pos();
}

void Form::mouseMoveEvent(QMouseEvent *event)
{
    QPointF disPointF = event->pos() - m_lastPointF;
    m_lastPointF = event->pos();
    view->scene()->setSceneRect(view->scene()->sceneRect().x()+disPointF.x(),
                                view->scene()->sceneRect().y()+disPointF.y(),
                                view->scene()->sceneRect().width(),
                                view->scene()->sceneRect().height());
    view->scene()->update();
}

void Form::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsPixmapItem *m_bkPixmapItem1 = new QGraphicsPixmapItem();
    m_bkPixmapItem1->setPixmap(QPixmap(":/3.bmp").scaled(1280,960,Qt::KeepAspectRatioByExpanding));
    m_bkPixmapItem1->setPos(2000,0);
    scene->addItem(m_bkPixmapItem1);
}
