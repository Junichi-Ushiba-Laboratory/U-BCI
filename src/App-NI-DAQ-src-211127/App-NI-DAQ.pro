QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PROGRAM_VERSION = "211001"

SOURCES += \
    DaqStreaming.c \
    DaqStreamingWrapper.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DaqSettings.h \
    DaqStreaming.h \
    DaqStreamingWrapper.h \
    LslSettings.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Path settings
PROJECT_PATH = $${_PRO_FILE_PWD_}
ROOT_PATH = $${PROJECT_PATH}/../../

# NI-DAQmx path
INCLUDEPATH += "C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/include"
win32: LIBS += "C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C/lib64/msvc/NIDAQmx.lib"

# LSL path
INCLUDEPATH += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/include
win32: LIBS += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/lib/lsl.lib

# Build path
release: DESTDIR = $${PROJECT_PATH}/../$${TARGET}-$${PROGRAM_VERSION}_build/release
debug:   DESTDIR = $${PROJECT_PATH}/../$${TARGET}-$${PROGRAM_VERSION}_build/debug
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
