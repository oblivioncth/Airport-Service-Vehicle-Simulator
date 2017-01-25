#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T17:36:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ASV_Sim_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pathing.cpp \
    car.cpp \
    plane.cpp

HEADERS  += mainwindow.h \
    pathing.h \
    car.h \
    plane.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    asv_res.qrc
