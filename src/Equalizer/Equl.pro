#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T13:49:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Equl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../eq2/equalizer.cpp

HEADERS  += mainwindow.h \
    ../eq2/equalizer.h \

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
