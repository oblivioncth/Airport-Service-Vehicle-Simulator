#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QtWidgets>
#include <math.h>
#include "car.h"
#include "pathing.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap pixmap(":/ui/Resources/Splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    w.show();
    splash.finish(&w);

    return a.exec();
}
