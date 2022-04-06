#-------------------------------------------------
#
# Project created by QtCreator 2012-04-28T00:14:43
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += network
TARGET = AudioCaptureWin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

symbian: LIBS += -lliblsl32-debug
else:unix|win32: LIBS += -L$$PWD/../../LSL/liblsl-1.14.0-Win_amd64/bin/ -lliblsl32-debug

#INCLUDEPATH += $$PWD/../../LSL/liblsl-1.14.0-Win_amd64/bin
#DEPENDPATH += $$PWD/../../LSL/liblsl-1.14.0-Win_amd64/bin

PROJECT_PATH = $${_PRO_FILE_PWD_}
ROOT_PATH = $${PROJECT_PATH}/../../
INCLUDEPATH += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/include
win32: LIBS += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/lib/lsl.lib

INCLUDEPATH += $$PWD/../../boost_1_77_0
DEPENDPATH += $$PWD/../../boost_1_77_0
