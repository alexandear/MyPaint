#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T17:35:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPaint
TEMPLATE = app

CONFIG += C++11


SOURCES += main.cpp \
    mainwindow.cpp \
    paintscene.cpp \
    datasingleton.cpp \
    abstractinstrument.cpp \
    pencilinstrument.cpp \
    lineinstrument.cpp \
    geometricshapesinstrument.cpp \
    instrumentswidget.cpp

HEADERS += \
    mainwindow.h \
    paintscene.h \
    datasingleton.h \
    abstractinstrument.h \
    pencilinstrument.h \
    instrumentsenum.h \
    lineinstrument.h \
    geometricshapesinstrument.h \
    instrumentswidget.h
