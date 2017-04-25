#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T17:14:01
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = orchestrix_sample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        GameplayWindow.cpp

HEADERS  += GameplayWindow.h

FORMS    += GameplayWindow.ui


INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
LIBS += -L/usr/local/lib/audio/ -laut
LIBS += -L/usr/local/lib/audio/ -lsndfile
LIBS += -L/usr/local/lib/audio/ -lfftw3
LIBS += -L/usr/local/lib/audio/ -lpthread
LIBS += -L/usr/local/lib/ -lalut
LIBS += -L/usr/local/lib/ -lopenal
