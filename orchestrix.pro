#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T23:35:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = orchestrix
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
INCLUDEPATH += src/windows \
               src/audio   \
               src/


SOURCES += src/main.cpp\
        src/windows/StartWindow.cpp \
    src/User.cpp \
    src/Game.cpp \
    src/windows/HelpDialog.cpp \
    src/windows/ResultsDialog.cpp \
    src/windows/LoginDialog.cpp \
    src/audio/AudioData.cpp \
    src/audio/AudioManager.cpp \
    src/audio/AudioPlayer.cpp \
    src/audio/Spectrum.cpp \
    src/audio/SpectrumAnalyzer.cpp

HEADERS  += src/windows/StartWindow.h \
    src/User.h \
    src/Game.h \
    src/windows/HelpDialog.h \
    src/windows/ResultsDialog.h \
    src/windows/LoginDialog.h \
    src/audio/AudioData.h \
    src/audio/AudioManager.h \
    src/audio/AudioPlayer.h \
    src/audio/OpenAL.h \
    src/audio/Spectrum.h \
    src/audio/SpectrumAnalyzer.h

FORMS    += src/windows/uis/StartWindow.ui \
    src/windows/uis/HelpDialog.ui \
    src/windows/uis/ResultsDialog.ui \
    src/windows/uis/LoginDialog.ui

LIBS+= -L/usr/local/lib -lopenal
LIBS+= -L/usr/local/lib -lalut
LIBS+= -L/usr/local/lib -lsndfile
LIBS+= -L/usr/local/lib -lpthread
LIBS+= -L/usr/local/lib -lprogbase-cpp
LIBS+= -L/usr/local/lib -lprogbase
LIBS+= -L/usr/local/lib -lssl
LIBS += -lbass
