#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T23:35:07
#
#-------------------------------------------------

QT       += core gui
QT += widgets

TARGET = orchestrix
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_Dsudo chmod 644 /usr/local/lib/libbass.soISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += src/windows \
               src/audio   \
               src/        \
               src/include  \
               src/Controller/byUSB/


SOURCES += src/main.cpp\
        src/windows/StartWindow.cpp \
    src/windows/HelpDialog.cpp \
    src/windows/ResultsDialog.cpp \
    src/windows/LoginDialog.cpp \
    src/audio/AudioData.cpp \
    src/audio/AudioManager.cpp \
    src/audio/AudioPlayer.cpp \
    src/audio/Spectrum.cpp \
    src/audio/SpectrumAnalyzer.cpp \
    src/windows/GameDialog.cpp  \
    src/windows/SoundHistogramm.cpp \
    src/windows/EQWidget.cpp \
    src/Indicator.cpp \
    src/Controller/byUSB/Controller.cpp   \
    src/Game.cpp \
    src/FileProcessing.cpp  \
    src/TableModel.cpp  \
    src/User.cpp \

HEADERS  += src/windows/StartWindow.h \
    src/include/User.h \
    src/include/Game.h \
    src/windows/HelpDialog.h \
    src/windows/ResultsDialog.h \
    src/windows/LoginDialog.h \
    src/audio/AudioData.h \
    src/audio/AudioManager.h \
    src/audio/AudioPlayer.h \
    src/audio/OpenAL.h \
    src/audio/Spectrum.h \
    src/audio/SpectrumAnalyzer.h \
    src/windows/GameDialog.h \
    src/windows/EQWidget.h \
    src/windows/SoundHistogramm.h \
    src/include/Indicator.h \
    src/include/FileProcessing.h  \
    src/include/TableModel.h  \
    src/Controller/byUSB/Controller.h \

FORMS    += src/windows/uis/StartWindow.ui \
    src/windows/uis/HelpDialog.ui \
    src/windows/uis/ResultsDialog.ui \
    src/windows/uis/LoginDialog.ui \
    src/windows/uis/GameDialog.ui \
    src/windows/uis/EQWidget.ui \
    src/windows/uis/SoundHistogramm.ui

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

unix:!macx: LIBS +=  -L$$PWD/libs/x64 -lbass
LIBS +=  -L$$PWD/libs -lbass

LIBS+= -L/usr/local/lib -lopenal
LIBS+= -L/usr/local/lib -lsndfile
LIBS+= -L/usr/local/lib -lpthread

RESOURCES += \
    res.qrc

DISTFILES += \
    res/result

