#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T18:59:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SO_TP2_ProcessSimRR_DanielKneipp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/Process.cpp \
    src/RoundRobin.cpp \
    src/SO_TP2_ProcessSim.cpp

HEADERS  += mainwindow.h \
    src/Process.h \
    src/RoundRobin.h

FORMS    += mainwindow.ui
