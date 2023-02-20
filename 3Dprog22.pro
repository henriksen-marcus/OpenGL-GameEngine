QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Actor.cpp \
    Arrow.cpp \
    BaseObject.cpp \
    Cube.cpp \
    Pawn.cpp \
    SceneComponent.cpp \
    Shader.cpp \
    XYZ.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp

HEADERS += \
    Actor.h \
    Arrow.h \
    BaseObject.h \
    Camera.h \
    Cube.h \
    Pawn.h \
    Renderer.h \
    SceneComponent.h \
    Shader.h \
    VertexClasses.h \
    VisualObject.h \
    XYZ.h \
    enums.h \
    logger.h \
    mainwindow.h \
    renderwindow.h

HEADERS += $$SOURCES

FORMS += \
    mainwindow.ui

DISTFILES += \
    fragment.frag \
    plainshader.frag \
    plainshader.vert \
    vertex.vert

