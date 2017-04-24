#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T14:54:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OrchEqualizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    equalizer.cpp \
    lineconnector.cpp

HEADERS  += mainwindow.h \
    equalizer.h \
    lineconnector.h

FORMS    += mainwindow.ui
