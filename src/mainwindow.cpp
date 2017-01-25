#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <math.h>
#include "car.h"
#include "plane.h"
#include <vector>
#include <QDebug>
#include "pathing.h"

using namespace std;

int iDoOnce[2] = {1,1};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup Main Window
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(this->size().width(), this->size().height());
    ui->pshbtnAdvFrame->setEnabled(false);
    ui->pshbtnPause->setEnabled(false);
    ui->lnSimSpeed->setEnabled(false);
    ui->pshbtnSpeedDwn->setEnabled(false);
    ui->pshbtnSpeedUp->setEnabled(false);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    //QGraphicsScene scene;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    Cars[0]->setPos(iCurrentX[0],iCurrentY[0]);
    Cars[0]->setRotation(90);
    scene->addItem(Cars[0]);
    iCarEnabled[0] = 0;

    Cars[1]->setPos(iCurrentX[1],iCurrentY[1]);
    Cars[1]->setRotation(90);
    scene->addItem(Cars[1]);
    iCarEnabled[1] = 0;

    Cars[2]->setPos(iCurrentX[2],iCurrentY[2]);
    Cars[2]->setRotation(90);
    scene->addItem(Cars[2]);
    iCarEnabled[2] = 0;

    Cars[3]->setPos(iCurrentX[3],iCurrentY[3]);
    Cars[3]->setRotation(90);
    scene->addItem(Cars[3]);
    iCarEnabled[3] = 1;

    Cars[4]->setPos(iCurrentX[4],iCurrentY[4]);
    Cars[4]->setRotation(90);
    scene->addItem(Cars[4]);
    iCarEnabled[4] = 0;

    Cars[5]->setPos(iCurrentX[5],iCurrentY[5]);
    Cars[5]->setRotation(90);
    scene->addItem(Cars[5]);
    iCarEnabled[5] = 0;

    Cars[6]->setPos(iCurrentX[6],iCurrentY[6]);
    Cars[6]->setRotation(90);
    scene->addItem(Cars[6]);
    iCarEnabled[6] = 0;

    Cars[7]->setPos(iCurrentX[7],iCurrentY[7]);
    Cars[7]->setRotation(90);
    scene->addItem(Cars[7]);
    iCarEnabled[7] = 0;

    //PLANES
    Planes->setPos(iPlaneCurrentX,iPlaneCurrentY);
    Planes->setRotation(180);
    scene->addItem(Planes);

    ui->gvSim->setScene(scene);
    //ui->gvSim->setRenderHint(QPainter::Antialiasing);
    ui->gvSim->setRenderHint(QPainter::NonCosmeticDefaultPen);
    ui->gvSim->setBackgroundBrush(QPixmap(":/ui/Resources/Background.jpg"));
    ui->gvSim->setCacheMode(QGraphicsView::CacheBackground);
    ui->gvSim->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->gvSim->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->gvSim->show();

    //Setup Algorithm
    fnSetupGrid();

    timer.setSingleShot(true);
    timer.start(iTimerBaseSpeed);
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotUpdate()));
}

void MainWindow::slotUpdate()
{
    for(int i = 0; i < 8; i++)
    {
            iCurrentY[i] = Cars[i]->y();
            iCurrentX[i] = Cars[i]->x();
            if(iNextX[i] == iCurrentX[i] && iNextY[i] == iCurrentY[i])
            {
                iCurrentYGrid[i] = iCurrentY[i]/10;
                iCurrentXGrid[i] = iCurrentX[i]/10;
            }
            if((iInitCheck[i] == 0 || fnCheckPathBlock(vPaths[i],iCurrentXGrid,iCurrentYGrid,i) == true) || iRecalc[i] == 1)
            {
                iInitCheck[i] = 1;
                fnUpdateGrid(i,iCurrentXGrid,iCurrentYGrid,"Set");
                vPaths[i] = fnFindPath(iCurrentXGrid[i],iCurrentYGrid[i],iDestinationX[i],iDestinationY[i]);
                fnUpdateGrid(i,iCurrentXGrid,iCurrentYGrid,"Reset");
                iRecalc[i] = 0;
            }
            if(vPaths[i].size() != 0)
            {
                  crdFirsts[i] = vPaths[i].front();
            }
            if((iNextX[i] == iCurrentX[i] && iNextY[i] == iCurrentY[i]) && vPaths[i].size() != 0)
            {
                  vPaths[i].erase(vPaths[i].begin());
            }
            iNextGridY[i] = crdFirsts[i].y;
            iNextGridX[i] = crdFirsts[i].x;
            iNextY[i] = (iNextGridY[i] * 10)+5;
            iNextX[i] = (iNextGridX[i]  * 10)+5;

            if(iCurrentY[i] == iNextY[i] && iCurrentX[i] == iNextX[i]) //Vehicle is on spot
            {
                iDirX[i] = 0;
                iDirY[i] = 0;
            }
            else if(iCurrentY[i] > iNextY[i] && iCurrentX[i] == iNextX[i]) //Vehicle needs to face north
            {
                Cars[i]->setRotation(0);
                iDirX[i] = 0;
                iDirY[i] = 1;
            }
            else if(iCurrentY[i] < iNextY[i] && iCurrentX[i] == iNextX[i]) //Vehicle needs to face south
            {
                Cars[i]->setRotation(180);
                iDirX[i] = 0;
                iDirY[i] = -1;
            }
            else if(iCurrentX[i] < iNextX[i] && iCurrentY[i] == iNextY[i]) //Vehicle needs to face east
            {
                Cars[i]->setRotation(90);
                iDirX[i] = 1;
                iDirY[i] = 0;
            }
            else if(iCurrentX[i] > iNextX[i] && iCurrentY[i] == iNextY[i]) //Vehicle needs to face west
            {
                Cars[i]->setRotation(270);
                iDirX[i] = -1;
                iDirY[i] = 0;
            }

            Cars[i]->setPos(iCurrentX[i]+(2*iDirX[i]*iCarEnabled[i]),iCurrentY[i]-(2*iDirY[i]*iCarEnabled[i]));
       }

        iPlaneCurrentY = Planes->y();
        iPlaneCurrentX = Planes->x();
       if(iPlaneCurrentX == iPlaneNextX && iPlaneCurrentY == iPlaneNextY)
       {
           if(iPlaneTask == 1)
           {
               iPlaneDirX = 1;
               iPlaneDirY = 0;
               Planes->setRotation(90);
               iPlaneNextX = 545;
               iPlaneNextY = 525;
               iPlaneTask++;
           }
           else if(iPlaneTask == 2)
           {
               iPlaneDirX = 0;
               iPlaneDirY = 1;
               Planes->setRotation(0);
               iPlaneNextX = 545;
               iPlaneNextY = 375;
               iPlaneTask++;
           }
           else if(iPlaneTask == 3 && iDoOnce[0] == 1)
           {
               iPlaneDirX = 0;
               iPlaneDirY = 0;
               iCarEnabled[0] = 1;
               iCarEnabled[1] = 1;
               iCarEnabled[2] = 1;
               iCarEnabled[3] = 1;
               iDoOnce[0] = 0;
           }
           else if(iPlaneTask == 4)
           {
                iPlaneDirX = 0;
                iPlaneDirY = 1;
                iPlaneNextX = 545;
                iPlaneNextY = 359;
                iPlaneTask++;
           }
           else if(iPlaneTask == 5)
           {
                iPlaneDirX = -1;
                iPlaneDirY = 0;
                iPlaneNextX = 343;
                iPlaneNextY = 359;
                Planes->setRotation(270);
                iPlaneTask++;
           }
           else if(iPlaneTask == 6)
           {
                iPlaneDirX = 0;
                iPlaneDirY = 1;
                iPlaneNextX = 343;
                iPlaneNextY = 225;
                Planes->setRotation(0);
                iPlaneTask++;
           }
           else if(iPlaneTask == 7)
           {
               iPlaneDirX = -1;
               iPlaneDirY = 0;
               iPlaneNextX = 305;
               iPlaneNextY = 225;
               Planes->setRotation(270);
               iPlaneTask++;
           }
           else if(iPlaneTask == 8)
           {
               iPlaneDirX = 0;
               iPlaneDirY = 1;
               iPlaneNextX = 305;
               iPlaneNextY = 69;
               Planes->setRotation(0);
               iPlaneTask++;
           }
           else if(iPlaneTask == 9 && iDoOnce[1] == 1)
           {
               iPlaneDirX = 0;
               iPlaneDirY = 0;
               iPlaneNextX = -1;
               iPlaneNextY = -1;
               iPlaneTask++;
               iDoOnce[1] = 0;
               iCarEnabled[4] = 1;
               iCarEnabled[5] = 1;
           }
       }
       Planes->setPos(iPlaneCurrentX+(2*iPlaneDirX),iPlaneCurrentY-(2*iPlaneDirY));
       fnScheduleChange();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fnScheduleChange()
{
    int iCurrentTaskNum[8];
    for(int i = 0; i < 8; i++)
    {
        iCurrentTaskNum[i] = iCarTaskNum[i];
    }
    for(int i = 0; i < 8; i++)
    {
        if(iCurrentXGrid[i] == iDestinationX[i] && iCurrentYGrid[i] == iDestinationY[i] && iTaskCompleteFlag[i] == 0)
        {
            fnLogUpdate("Car" + QString::number(i) + " has arrived at its destination");
            iTaskCompleteFlag[i] = 1;
            iCarTaskNum[i]++;
        }

    }

    //ADD IN LOGIC FOR DESTINATION SWITCHES
    if(iCurrentTaskNum[3] == 2 && iTaskCompleteFlag[3] == 1)
    {
       iDestinationX[3] = 48;
       iDestinationY[3] = 36;
       iRecalc[3] = 1;
       iCarEnabled[3] = 0;
    }
    if(iCurrentTaskNum[3] == 3 && iTaskCompleteFlag[3] == 1)
    {
       iDestinationX[3] = 52;
       iDestinationY[3] = 48;
       iRecalc[3] = 1;
       iCarEnabled[3] = 1;

    }
    if(iCurrentTaskNum[3] == 4 && iTaskCompleteFlag[3] == 1)
    {
       iDestinationX[3] = 75;
       iDestinationY[3] = 50;
       iRecalc[3] = 1;
       iCarEnabled[3] = 1;
    }
    if(iCurrentTaskNum[3] == 5 && iTaskCompleteFlag[3] == 1)
    {
       iDestinationX[3] = -1;
       iDestinationY[3] = -1;
       iCarEnabled[3] = 0;

       //NEXT PHASE
       iPlaneTask++;
    }


    //Cars at plane
    if(iCurrentTaskNum[0] == 2 && iTaskCompleteFlag[0] == 1)
    {
        iDestinationX[0] = 71;
        iDestinationY[0] = 52;
        iCarEnabled[0] = 0;
        iRecalc[0] = 1;
    }
    if(iCurrentTaskNum[1] == 2 && iTaskCompleteFlag[1] == 1)
    {
        iDestinationX[1] = 69;
        iDestinationY[1] = 55;
        iCarEnabled[1] = 0;
        iRecalc[1] = 1;
    }
    if(iCurrentTaskNum[2] == 2 && iTaskCompleteFlag[2] == 1)
    {
        iDestinationX[2] = 75;
        iDestinationY[2] = 55;
        iCarEnabled[2] = 0;
        iCarEnabled[1] = 1;
        iCarEnabled[0] = 1;
        iCarEnabled[3] = 0;
        iRecalc[2] = 1;
    }
    if(iCurrentTaskNum[2] == 3 && iTaskCompleteFlag[2] == 1)
    {
        iDestinationX[2] = -1;
        iDestinationY[2] = -1;
    }
    if(iCurrentTaskNum[1] == 3 && iTaskCompleteFlag[1] == 1)
    {
        iDestinationX[1] = -1;
        iDestinationY[0] = -1;
        iCarEnabled[1] = 0;
        iCarEnabled[0] = 0;
        iCarEnabled[2] = 1;
        iCarEnabled[3] = 1;
        iCarEnabled[4] = 1;
    }

    //2nd PHASE
    if(iCurrentTaskNum[4] == 2 && iTaskCompleteFlag[4] == 1)
    {
        iDestinationX[4] = 28;
        iDestinationY[4] = 12;
        iCarEnabled[4] = 0;
        iRecalc[4] = 1;
    }
    if(iCurrentTaskNum[4] == 3 &&  iTaskCompleteFlag[4] == 1)
    {
        iDestinationX[4] = 56;
        iDestinationY[4] = 45;
        iCarEnabled[4] = 0;
        iRecalc[4] = 1;
        timer.stop();
    }
    if(iCurrentTaskNum[5] == 2 && iTaskCompleteFlag[5] == 1)
    {
        iDestinationX[5] = -1;
        iDestinationY[5] = -1;
        iCarEnabled[5] = 0;
    }




    for(int i = 0; i < 8; i++) //Reset task complete flag if new task was assigned.
    {
        if(iCurrentTaskNum[i] != iCarTaskNum[i])
            iTaskCompleteFlag[i] = 0;
    }
}

void MainWindow::fnLogUpdate(QString qsMesg)
{
    int iElapsed = simtime.elapsed();
    int iMin = iElapsed/60000;
    int iSec = (iElapsed/1000) - (iMin*60);
    QString qsSimTime;
    QString qsSec = QString::number(iSec);
    QString qsMin = QString::number(iMin);
    if(iMin < 10)
        qsMin.prepend("0");
    if(iSec < 10)
        qsSec.prepend("0");
    qsSimTime = qsMin + ":" + qsSec;
    ui->pteLog->appendPlainText("["+qsSimTime+"]:");
    ui->pteLog->appendPlainText(qsMesg);
    qApp->processEvents();
}


void MainWindow::on_pshbtnPause_clicked()
{
    if(ui->pshbtnPause->text() == "Pause")
    {
        ui->pshbtnPause->setText("Resume");
        timer.setSingleShot(true);
        timer.stop();
        ui->pshbtnAdvFrame->setEnabled(true);

    }
    else
    {
        ui->pshbtnPause->setText("Pause");
        timer.setSingleShot(false);
        timer.start();
        ui->pshbtnAdvFrame->setEnabled(false);
    }
}

void MainWindow::on_pshbtnAdvFrame_clicked()
{
    timer.start();
}

void MainWindow::on_pshbtnSpeedUp_clicked()
{
    if(ui->lnSimSpeed->text() == "2x")
    {
        ui->lnSimSpeed->setText("3x");
        timer.start(iTimerBaseSpeed/3);
    }
    if(ui->lnSimSpeed->text() == "1.5x")
    {
        ui->lnSimSpeed->setText("2x");
        timer.start(iTimerBaseSpeed/2);
    }
    if(ui->lnSimSpeed->text() == "1x")
    {
        ui->lnSimSpeed->setText("1.5x");
        timer.start(iTimerBaseSpeed/1.5);
    }
    if(ui->lnSimSpeed->text() == "0.5x")
    {
        ui->lnSimSpeed->setText("1x");
        timer.start(iTimerBaseSpeed);
    }
    if(ui->lnSimSpeed->text() == "0.25x")
    {
       ui->lnSimSpeed->setText("0.5x");
       timer.start(iTimerBaseSpeed*2);
    }
    if(ui->lnSimSpeed->text() == "0.125x")
    {
       ui->lnSimSpeed->setText("0.25x");
       timer.start(iTimerBaseSpeed*4);
    }
}

void MainWindow::on_pshbtnSpeedDwn_clicked()
{
    if(ui->lnSimSpeed->text() == "0.25x")
    {
       ui->lnSimSpeed->setText("0.125x");
       timer.start(iTimerBaseSpeed*8);
    }
    if(ui->lnSimSpeed->text() == "0.5x")
    {
       ui->lnSimSpeed->setText("0.25x");
       timer.start(iTimerBaseSpeed*4);
    }
    if(ui->lnSimSpeed->text() == "1x")
    {
       ui->lnSimSpeed->setText("0.5x");
       timer.start(iTimerBaseSpeed*2);
    }
    if(ui->lnSimSpeed->text() == "1.5x")
    {
       ui->lnSimSpeed->setText("1x");
       timer.start(iTimerBaseSpeed);
    }
    if(ui->lnSimSpeed->text() == "2x")
    {
       ui->lnSimSpeed->setText("1.5x");
       timer.start(iTimerBaseSpeed/1.5);
    }
    if(ui->lnSimSpeed->text() == "3x")
    {
       ui->lnSimSpeed->setText("2x");
       timer.start(iTimerBaseSpeed/2);
    }
}

void MainWindow::on_actionStart_Simulation_triggered()
{
    ui->pshbtnPause->setEnabled(true);
    ui->lnSimSpeed->setEnabled(true);
    ui->pshbtnSpeedDwn->setEnabled(true);
    ui->pshbtnSpeedUp->setEnabled(true);
    timer.setSingleShot(false);
    timer.start();
    simtime.start();
    fnLogUpdate("Simulation started.");
}
