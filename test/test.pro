QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# INCLUDEPATH += "lib/googletest/googletest/include"
# INCLUDEPATH += "lib/googletest/googletest"

SOURCES += \
        ../src/chainitem.cpp \
        ../src/item.cpp \
        ../src/key.cpp \
        ../src/lamp.cpp \
        ../src/mathsign.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../lib/googletest/lib/ -lgtest

INCLUDEPATH += $$PWD/../lib/googletest/include/googletest/include
DEPENDPATH += $$PWD/../lib/googletest/include/googletest/include

HEADERS += \
    ../src/chainitem.h \
    ../src/item.h \
    ../src/key.h \
    ../src/lamp.h \
    ../src/mathsign.h
