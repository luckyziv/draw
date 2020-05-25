#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BT_selectFile->setText("Select File!");
    setWindowTitle("Draw Dialog");
    btText = "";
    fileName = "";
    dataFile = NULL;

    //form1 = new Form();
    //form1->show();
#if 0
    QPainter painter(this);
    QPainterPath paintPath;
#endif
}

MainWindow::~MainWindow()
{
    dataFile->close();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

#if 1
    QPainter painter(this);
    QPainterPath paintPath;

    paintPath.moveTo(50, 100);

    paintPath.lineTo(100, 150);

    painter.drawPath(paintPath);
#endif

}

void MainWindow::on_BT_selectFile_clicked()
{
    if (btText.isEmpty()) {
        fileName = QFileDialog::getOpenFileName(this,
                                                tr("Select File Dialog"),
                                                "C:");
        qDebug()<<"fileName:"<<fileName;
        if(!fileName.isEmpty()) {
            ui->LE_filePath->setText(fileName);
            btText = "sure";
            ui->BT_selectFile->setText(btText);
        }
    } else {
        // border data process
        qDebug()<<"read file success！";
        dataFile = new QFile(fileName);
        bool ret = dataFile->open(QIODevice::ReadOnly);
        if (ret) {
            QByteArray data;
            QString str0, str1;
            QString allString;
            QString borderPointCordnte, startPointCordnte, endPointCordnte;
            QString strTemp;
            QStringList borderPointList, startPointList, endPointList;
            int idxStart, idxEnd, count;

            data = dataFile->readAll();     // all file context in data
            allString = data;               // QByteArray to QString

            // step1. read border data and analyse
            str0 = borderFlagString;
            str1 = resFlagString;

            idxStart = allString.indexOf(str0);
            idxEnd = allString.indexOf(str1);
            borderPointCordnte = allString.mid(idxStart + str0.length(), (idxEnd - (idxStart + str0.length())));
            borderPointCordnte = borderPointCordnte.replace(QString("\r\n"), QString(""));
#if 0
            qDebug()<<allString; //            qDebug()<<allString.indexOf(str0)
                   <<allString.indexOf(str1);
            qDebug()<<allString.mid(idxStart + str0.length(), (idxEnd - (idxStart + str0.length())));
            qDebug()<<borderPointCordnte.replace(QString("\r\n"), QString(""));
#endif
            strTemp = borderPointCordnte;
            count = 0;

            QRegExp reg0("-?\\d+\\.?\\d+");
            for(int pos=0; pos=reg0.indexIn(strTemp,pos),pos>=0; pos+=reg0.matchedLength()) {
                //qDebug()<<pos; //返回查找到序号
                borderPointList.append(reg0.cap(0));
            }
            if ((!borderPointList.isEmpty()) && !((borderPointList.count())%2)) {
                qDebug() << "borderPointList is not NULL!";
                count = borderPointList.count()/2;

//                borderPointCoordinate coordnate[count];
                // border data
                allData.borderPointsNum = count;

                QString strToDouble;
                for (int i = 0, j = 0; i < count; i++, j++) {
                    strToDouble = borderPointList.at(j);
                    //coordnate[i].x = -(strToDouble.toDouble());
                    allData.borderPointsArray[i].x = -(strToDouble.toDouble());

                    strToDouble = borderPointList.at(++j);
                    //coordnate[i].y = -(strToDouble.toDouble());
                    allData.borderPointsArray[i].y = -(strToDouble.toDouble());
#if 0
                    //printf("%f %f\r\n", coordnate[i].x, coordnate[i].y);
                    //qDebug() << i;
                    //qDebug() << coordnate[i].x << coordnate[i].y << endl;
#endif
                }
            // step2. read start points data and analyse
            str0 = startFlagString;
            str1 = endFlagString;
            idxStart = allString.indexOf(str0);
            idxEnd = allString.indexOf(str1);
            startPointCordnte = allString.mid(idxStart + str0.length(), (idxEnd - (idxStart + str0.length())));
            startPointCordnte = startPointCordnte.replace(QString("\r\n"), QString(""));
            //startPointCordnte = startPointCordnte.replace(QString(" "), QString(""));
            qDebug() << startPointCordnte;

            strTemp = startPointCordnte;
            QRegExp reg1("\\(-?\\d+\\.?\\d+\\,-?\\d+\\.?\\d+\\)");
            for(int pos=0; pos=reg1.indexIn(strTemp,pos),pos>=0; pos+=reg1.matchedLength()) {
                //qDebug()<<pos; //返回查找到序号
                startPointList.append(reg1.cap(0));
            }
            qDebug() << startPointList;


            // step3. read end poingts data and analyse

            // step4. read min space data


//                this->hide();
//                form1 = new Form();
//                form1->show();
            } else {
                qDebug() << "borderPointList is NULL!";
            }
//            qDebug() << "ljlj \n" << borderPointList << "\n " << borderPointList.count() << "\n" << borderPointList.at(0);
        } else {
            qDebug()<<"file open failed!";
        }
    };
}
