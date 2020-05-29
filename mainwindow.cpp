#include "mainwindow.h"
#include "ui_mainwindow.h"

coordinateData allData;

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

    form1 = new Form();
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
            QString borderPointCordnte, startPointCordnte, endPointCordnte, miniWidthStr;
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
            //qDebug() << "border point coordinate data0: \r\n" << strTemp;

            QRegExp reg0("-?\\d+\\.?\\d+");
            for(int pos=0; pos=reg0.indexIn(strTemp,pos),pos>=0; pos+=reg0.matchedLength()) {
                borderPointList.append(reg0.cap(0));
            }
            qDebug() << "border point coordinate list: \r\n" << borderPointList;

            if ((!borderPointList.isEmpty()) && !((borderPointList.count())%2)) {
                count = 0;
                count = borderPointList.count()/2;

                allData.borderPointsNum = count;
                QString strToDouble;
                for (int i = 0, j = 0; i < count; i++, j++) {
                    strToDouble = borderPointList.at(j);
                    //coordnate[i].x = -(strToDouble.toDouble());
                    allData.borderPointsArray[i].x = strToDouble.toDouble();

                    strToDouble = borderPointList.at(++j);
                    //coordnate[i].y = -(strToDouble.toDouble());
                    allData.borderPointsArray[i].y = -(strToDouble.toDouble());
                }

            } else {
                qDebug() << "borderPointList is NULL!";
            }

            // step2. read start points data and analyse
            str0 = startFlagString;
            str1 = endFlagString;
            idxStart = allString.indexOf(str0);
            idxEnd = allString.indexOf(str1);
            startPointCordnte = allString.mid(idxStart + str0.length(), (idxEnd - (idxStart + str0.length())));
            startPointCordnte = startPointCordnte.replace(QString("\r\n"), QString(""));
            //qDebug() << " start point coordinate data0: \r\n" << startPointCordnte;

            strTemp = startPointCordnte;
            QString startTemp = "";
            QRegExp reg1("\\(-?\\d+\\.?\\d+\\,-?\\d+\\.?\\d+\\)");
            for(int pos = 0; pos = reg1.indexIn(strTemp, pos), pos>=0; pos += reg1.matchedLength()) {
                startTemp += reg1.cap(0);
            }
            //qDebug() << " start poing coordinate data1: \r\n" << startTemp;

            QString startTemp2 = startTemp;
            QRegExp reg2("-?\\d+\\.?\\d+");
            for(int pos1 = 0; pos1 = reg2.indexIn(startTemp2, pos1), pos1 >= 0; pos1 += reg2.matchedLength()) {
                startPointList.append(reg2.cap(0));
            }
            qDebug() << " start point coordinate list: \r\n" << startPointList << startPointList.count();

            count = 0 ;
            count = startPointList.count()/4;
            allData.startPointsNum = count;

            if ((!startPointList.isEmpty()) && !((startPointList.count())%4)) {
                QString strToDouble;
                for (int i = 0, j = 0; i < count; i++, j++) {
                    strToDouble = startPointList.at(j);
                    allData.startPointsArray[i].pointStartX = strToDouble.toDouble();
                    strToDouble = startPointList.at(++j);
                    allData.startPointsArray[i].pointStartY = -(strToDouble.toDouble());

                    strToDouble = startPointList.at(++j);
                    allData.startPointsArray[i].pointEndX = strToDouble.toDouble();
                    strToDouble = startPointList.at(++j);
                    allData.startPointsArray[i].pointEndY = -(strToDouble.toDouble());

//                    qDebug() << allData.startPointsArray[i].pointStartX << allData.startPointsArray[i].pointStartY
//                             << allData.startPointsArray[i].pointEndX << allData.startPointsArray[i].pointEndY;
                }
            } else {
                qDebug() << "startPointList is NULL!";
            }

            // step3. read end poingts data and analyse
            str0 = endFlagString;
            str1 = borderFlagString;
            idxStart = allString.indexOf(str0);
            idxEnd = allString.indexOf(str1);
            endPointCordnte = allString.mid(idxStart + str0.length(), (idxEnd - (idxStart + str0.length())));
            endPointCordnte = endPointCordnte.replace(QString("\r\n"), QString(""));
            //qDebug() << " end point coordinate data0: \r\n" << endPointCordnte;

            strTemp = endPointCordnte;
            QString endTemp = "";
            QRegExp reg3("\\(-?\\d+\\.?\\d+\\,-?\\d+\\.?\\d+\\)");
            for(int pos = 0; pos = reg3.indexIn(strTemp, pos), pos>=0; pos += reg3.matchedLength()) {
                endTemp += reg3.cap(0);
            }
            //qDebug() << " start poing coordinate data1: \r\n" << startTemp;

            QString endTemp2 = endTemp;
            QRegExp reg4("-?\\d+\\.?\\d+");
            for(int pos1 = 0; pos1 = reg4.indexIn(endTemp2, pos1), pos1 >= 0; pos1 += reg4.matchedLength()) {
                endPointList.append(reg4.cap(0));
            }
            qDebug() << " end point coordinate list: \r\n" << endPointList << endPointList.count();

            count = 0 ;
            count = endPointList.count()/4;
            allData.endPointsNum = count;

            if ((!endPointList.isEmpty()) && !((endPointList.count())%4)) {
                QString strToDouble;
                for (int i = 0, j = 0; i < count; i++, j++) {
                    strToDouble = endPointList.at(j);
                    allData.endPointsArray[i].pointStartX = strToDouble.toDouble();
                    strToDouble = endPointList.at(++j);
                    allData.endPointsArray[i].pointStartY = -(strToDouble.toDouble());

                    strToDouble = endPointList.at(++j);
                    allData.endPointsArray[i].pointEndX = strToDouble.toDouble();
                    strToDouble = endPointList.at(++j);
                    allData.endPointsArray[i].pointEndY = -(strToDouble.toDouble());
                }
            } else {
                qDebug() << "startPointList is NULL!";
            }

            // step4. read min space data
            str0 = miniWidth;
            idxStart = allString.indexOf(str0);
            miniWidthStr = allString.mid(idxStart + str0.length(), 50);

            QRegExp reg5("\\d+\\.?\\d+");
            QString minWidthTmp = "";
            for(int pos1 = 0; pos1 = reg5.indexIn(miniWidthStr, pos1), pos1 >= 0; pos1 += reg5.matchedLength()) {
                minWidthTmp = reg5.cap(0);
            }
            allData.minWidth = minWidthTmp.toFloat();
            qDebug() << allData.minWidth;

            this->hide();
            form1 = new Form();
            form1->show();
        } else {
            qDebug()<<"file open failed!";
        }
    };
}
