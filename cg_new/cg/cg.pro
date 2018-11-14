#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T14:28:37
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
    rendercontext.cpp \
    bitmap.cpp \
    vector4f.cpp \
    vertex.cpp \
    gradient.cpp \
    edge.cpp \
    mesh.cpp \
    camera.cpp \
    objmodel.cpp \
    quaternion.cpp \
    matrix4f.cpp \
    transform.cpp \
    indexedmodel.cpp \
    texture.cpp

HEADERS += \
        mainwindow.h \
    rendercontext.h \
    bitmap.h \
    vector4f.h \
    vertex.h \
    gradient.h \
    window_size.h \
    edge.h \
    mesh.h \
    camera.h \
    objmodel.h \
    quaternion.h \
    matrix4f.h \
    transform.h \
    indexedmodel.h \
    texture.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
