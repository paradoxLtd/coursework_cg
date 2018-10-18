#-------------------------------------------------
#
# Project created by QtCreator 2018-09-09T00:13:18
#
#-------------------------------------------------

QT       += core gui widgets opengl

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
    object.cpp \
    options.cpp \
    point.cpp \
    scene.cpp \
    transformation.cpp \
    triangle.cpp \
    vector.cpp \
    objectlist.cpp \
    camera.cpp \
    point_debug.cpp \
    vector_debug.cpp \
    plane.cpp \
    triangle_debug.cpp \
    object_debug.cpp \
    loader.cpp \
    loader_debug.cpp \
    drawer.cpp \
    camera_debug.cpp \
    objectlist_debug.cpp \
    scene_debug.cpp \
    light/light.cpp \
    light/material.cpp \
    indexes.cpp \
    matrix.cpp \
    textures/textures.cpp \
    bitmap.cpp \
    textures/gradient.cpp \
    edge.cpp \
    vertex.cpp


HEADERS += \
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
    objectlist.h \
    debug.h \
    plane.h \
    errors.h \
    drawer.h \
    light/light.h \
    light/material.h \
    mainwindow.h \
    matrix.h \
    textures/textures.h \
    bitmap.h \
    fixed.h \
    textures/gradient.h \
    edge.h \
    vertex.h \
    defines.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
