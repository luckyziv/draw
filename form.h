#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "typedef.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

protected:
    void paintEvent(QPaintEvent *event);


private:
    Ui::Form *ui;
    QPainter *painter;
};

#endif // FORM_H
