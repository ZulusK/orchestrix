#-------------------------------------------------
#
# Project created by QtCreator 2017-05-15T23:36:02
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

INCLUDEPATH += src/windows/
INCLUDEPATH += src/gameplay/
INCLUDEPATH += src/Audio/
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
    src/gameplay/User.cpp \
    src/gameplay/Game.cpp \
    src/Audio/AudioData.cpp \
    src/Audio/AudioManager.cpp \
    src/Audio/AudioPlayer.cpp \
    src/Audio/Spectrum.cpp \
    src/Audio/SpectrumAnalyzer.cpp \
    src/gameplay/Controller.cpp \
    src/windows/GameDialog.cpp \
    src/windows/LoginDialog.cpp \
    src/windows/ResultsDialog.cpp \
    src/windows/MenuDialog.cpp \
    src/windows/HelpDialog.cpp

HEADERS  += \
    src/gameplay/User.h \
    src/gameplay/Game.h \
    src/Audio/AudioData.h \
    src/Audio/AudioManager.h \
    src/Audio/AudioPlayer.h \
    src/Audio/OpenAL.h \
    src/Audio/Spectrum.h \
    src/Audio/SpectrumAnalyzer.h \
    src/gameplay/Controller.h \
    src/windows/GameDialog.h \
    src/windows/LoginDialog.h \
    src/windows/ResultsDialog.h \
    src/windows/MenuDialog.h \
    src/windows/HelpDialog.h

FORMS    += \
    src/windows/uis/GameDialog.ui \
    src/windows/uis/LoginDialog.ui \
    src/windows/uis/ResultsDialog.ui \
    src/windows/uis/MenuDialog.ui \
    src/windows/uis/HelpDialog.ui


LIBS += -lbass
LIBS+= -L/usr/local/lib -laut
LIBS+= -L/usr/local/lib -lopenal
LIBS+= -L/usr/local/lib -lalut
LIBS+= -L/usr/local/lib -lfftw3
LIBS+= -L/usr/local/lib -lsndfile
LIBS+= -L/usr/local/lib -lpthread
LIBS+= -L/usr/local/lib -lprogbase-cpp
LIBS+= -L/usr/local/lib -lprogbase
