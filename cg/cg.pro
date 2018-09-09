#-------------------------------------------------
#
# Project created by QtCreator 2018-09-09T00:13:18
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = cg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    indexes.cpp \
    object.cpp \
    options.cpp \
    point.cpp \
    scene.cpp \
    transformation.cpp \
    triangle.cpp \
    vector.cpp \
    camera.cpp \
    plane.cpp

HEADERS += \
        mainwindow.h \
    bit.h \
    camera.h \
    loader.h \
    object.h \
    options.h \
    point.h \
    resource.h \
    scene.h \
    transformation.h \
    triangle.h \
    trianglelist.h \
    vector.h \
    indexes.h \
    plane.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
