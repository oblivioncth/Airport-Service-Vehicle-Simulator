#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "car.h"
#include "plane.h"
#include <vector>
#include "pathing.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pshbtnPause_clicked();

    void on_pshbtnAdvFrame_clicked();

    void on_pshbtnSpeedUp_clicked();

    void on_pshbtnSpeedDwn_clicked();

    void on_actionStart_Simulation_triggered();

public slots:
    void slotUpdate();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QTimer timer;
    int iTimerBaseSpeed = 25;
    QTime simtime;

    Plane *Planes = new Plane;
    Car *Cars[8] = {new Car,new Car,new Car,new Car,new Car,new Car,new Car,new Car};
    vector<Coordinates> vPaths[8];
    Coordinates crdFirsts[8];

    int iCarStartX[8] = {755,755,715,695,545,585,625,665}; //In Pixel units
    int iCarStartY[8] = {455,505,525,555,45,45,45,45}; //In Pixel units
    int iCarEnabled[8] = {1,1,1,1,1,1,1,1};
    int iDestinationX[8] = {57,57,50,26,6,33,55,57}; //In Grid units
    int iDestinationY[8] = {34,39,47,43,27,12,53,53}; //In Grid units
    int iCarTaskNum[8] = {1,1,1,1,1,1,1,1};
    int iTaskCompleteFlag[8] = {0,0,0,0,0,0,0,0};

    int iCurrentX[8] = {iCarStartX[0],iCarStartX[1],iCarStartX[2],iCarStartX[3],iCarStartX[4],iCarStartX[5],iCarStartX[6],iCarStartX[7]};
    int iCurrentY[8] = {iCarStartY[0],iCarStartY[1],iCarStartY[2],iCarStartY[3],iCarStartY[4],iCarStartY[5],iCarStartY[6],iCarStartY[7]};
    int iCurrentXGrid[8] = {iCarStartX[0]/10,iCarStartX[1]/10,iCarStartX[2]/10,iCarStartX[3]/10,iCarStartX[4]/10,iCarStartX[5]/10,iCarStartX[6]/10,iCarStartX[7]/10};
    int iCurrentYGrid[8] = {iCarStartY[0]/10,iCarStartY[1]/10,iCarStartY[2]/10,iCarStartY[3]/10,iCarStartY[4]/10,iCarStartY[5]/10,iCarStartY[6]/10,iCarStartY[7]/10};

    int iNextGridY[8];
    int iNextGridX[8];
    int iNextY[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int iNextX[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int iDirY[8] = {1,1,1,1,1,1,1,1};
    int iDirX[8] = {1,1,1,1,1,1,1,1};
    int iInitCheck[8] = {0,0,0,0,0,0,0,0};

    int iPlaneStartX = 155;
    int iPlaneStartY = 105;
    int iPlaneNextX = 155;
    int iPlaneNextY = 525;
    int iPlaneTask = 1;
    int iPlaneCurrentX = iPlaneStartX;
    int iPlaneCurrentY = iPlaneStartY;
    int iPlaneDirX = 0;
    int iPlaneDirY = -1;

    int iRecalc[8] = {0,0,0,0,0,0,0,0};

    void fnLogUpdate(QString qsMesg);
    void fnScheduleChange();
};



#endif // MAINWINDOW_H
