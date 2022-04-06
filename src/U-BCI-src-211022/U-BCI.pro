QT       += core gui
QT       += network
QT       += charts
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PROGRAM_VERSION = "211022"

SOURCES += \
    ApplicationSettings.cpp \
    OutputModule/HttpOutputModule.cpp \
    MatlabInterface/MatlabInterface.cpp \
    OutputModule/NiDaqOutputModule.cpp \
    OnlineProcessingModule/OnlineProcessingModule.cpp \
    OnlineProcessingModule/OnlineProcessingModuleManager.cpp \
    OnlineProcessingModule/OnlineProcessingModuleSettings.cpp \
    OutputModule/OutputModuleManager.cpp \
    OutputModule/OutputModuleSettings.cpp \
    StreamData/StreamDataChart.cpp \
    StreamData/StreamDataChartWindow.cpp \
    StreamData/StreamDataPreprocessor.cpp \
    StreamData/StreamDataPreprocessorManager.cpp \
    StreamData/StreamDataSettings.cpp \
    OutputModule/UdpOutputModule.cpp \
    Utility.cpp \
    main.cpp \
    mainwindow.cpp \
    LabRecorder/recording.cpp \
    LabRecorder/tcpinterface.cpp \
    LabRecorder/xdfwriter.cpp

HEADERS += \
    ApplicationSettings.h \
    OutputModule/HttpOutputModule.h \
    MatlabInterface/MatlabInterface.h \
    OutputModule/NiDaqOutputModule.h \
    OnlineProcessingModule/OnlineProcessingModule.h \
    OnlineProcessingModule/OnlineProcessingModuleManager.h \
    OnlineProcessingModule/OnlineProcessingModuleSettings.h \
    OutputModule/OutputModuleManager.h \
    OutputModule/OutputModuleSettings.h \
    StreamData/StreamData.h \
    StreamData/StreamDataChart.h \
    StreamData/StreamDataChartWindow.h \
    StreamData/StreamDataPreprocessor.h \
    StreamData/StreamDataPreprocessorManager.h \
    StreamData/StreamDataSettings.h \
    OutputModule/UdpOutputModule.h \
    LabRecorder/conversions.h \
    UbciException.h \
    Utility.h \
    mainwindow.h \
    LabRecorder/recording.h \
    LabRecorder/tcpinterface.h \
    LabRecorder/xdfwriter.h

FORMS += \
    StreamData/StreamDataChartWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Path settings
PROJECT_PATH = $${_PRO_FILE_PWD_}
ROOT_PATH = $${PROJECT_PATH}/../../
MATLAB_PATH = "C:/Program Files/MATLAB/R2021a"

# LSL path
INCLUDEPATH += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/include
win32: LIBS += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/lib/lsl.lib

# MATLAB engine path
INCLUDEPATH += $${MATLAB_PATH}/extern/include
DEPENDPATH  += $${MATLAB_PATH}/extern/include
MATLAB_LIB_PATH = $${MATLAB_PATH}/extern/lib/win64/microsoft
LIBS += $${MATLAB_LIB_PATH}/libMatlabEngine.lib
LIBS += $${MATLAB_LIB_PATH}/libMatlabDataArray.lib

# Build path
release: DESTDIR = $${PROJECT_PATH}/../$${TARGET}-$${PROGRAM_VERSION}_build/release
debug:   DESTDIR = $${PROJECT_PATH}/../$${TARGET}-$${PROGRAM_VERSION}_build/debug
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
