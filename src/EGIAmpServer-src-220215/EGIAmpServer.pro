QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    EGIAmpWindow.cpp

HEADERS += \
    EGIAmpWindow.h

FORMS += \
    EGIAmpWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# LSL path
PROJECT_PATH = $${_PRO_FILE_PWD_}
ROOT_PATH = $${PROJECT_PATH}/../../
INCLUDEPATH += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/include
win32: LIBS += $${ROOT_PATH}/LSL/liblsl-1.14.0-Win_amd64/lib/lsl.lib

#INCLUDEPATH += C:\boost_1_76_0
#win32:LIBS += C:\boost_1_76_0\build\x86\boost\bin.v2\libs\date_time\build\msvc-14.1\release\address-model-32\link-static\threading-multi/libboost_date_time-vc141-mt-x32-1_76.lib
#win32:LIBS += C:\boost_1_76_0\build\x86\boost\bin.v2\libs\date_time\build\msvc-14.1\debug\address-model-32\link-static\threading-multi/libboost_date_time-vc141-mt-gd-x32-1_76.lib
#win32:LIBS += C:\boost_1_76_0\build\x64\boost\bin.v2\libs\date_time\build\msvc-14.1\release\link-static\threading-multi\libboost_date_time-vc141-mt-x64-1_76.lib
#win32:LIBS += C:\boost_1_76_0\build\x64\boost\bin.v2\libs\date_time\build\msvc-14.1\debug\link-static\threading-multi\libboost_date_time-vc141-mt-gd-x64-1_76.lib

INCLUDEPATH += $$PWD/../../boost_1_77_0
DEPENDPATH += $$PWD/../../boost_1_77_0
win32:LIBS += $$PWD/../../boost_1_77_0\build\x86\boost\bin.v2\libs\date_time\build\msvc-14.1\release\address-model-32\link-static\threading-multi/libboost_date_time-vc141-mt-x32-1_77.lib
win32:LIBS += $$PWD/../../boost_1_77_0\build\x86\boost\bin.v2\libs\date_time\build\msvc-14.1\debug\address-model-32\link-static\threading-multi/libboost_date_time-vc141-mt-gd-x32-1_77.lib
win32:LIBS += $$PWD/../../boost_1_77_0\build\x64\boost\bin.v2\libs\date_time\build\msvc-14.1\release\link-static\threading-multi\libboost_date_time-vc141-mt-x64-1_77.lib
win32:LIBS += $$PWD/../../boost_1_77_0\build\x64\boost\bin.v2\libs\date_time\build\msvc-14.1\debug\link-static\threading-multi\libboost_date_time-vc141-mt-gd-x64-1_77.lib
