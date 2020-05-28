#ifndef FORM_H
#define FORM_H

#include "common.h"
#include <QMainWindow>
//#include "myitem.h"

class MyItem;

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);


private:
    Ui::Form *ui;
    QPainter *painter;

    QGraphicsScene *scene;
    QGraphicsView *view;
//    MyItem item;

    QWidget* sceneWidget;

    QGraphicsPixmapItem* m_bkPixmapItem;

    QPointF m_lastPointF;
    qreal m_scale;
};

#endif // FORM_H
