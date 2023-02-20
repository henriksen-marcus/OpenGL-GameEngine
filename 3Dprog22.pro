QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Actor.cpp \
    Arrow.cpp \
    Axis.cpp \
    BaseObject.cpp \
    Cube.cpp \
    Pawn.cpp \
    SceneComponent.cpp \
    Shader.cpp \
    VisualFunction2D.cpp \
    VisualFunction3D.cpp \
    XYZ.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    VisualPoints.cpp

HEADERS += \
    Actor.h \
    Arrow.h \
    Axis.h \
    BaseObject.h \
    Camera.h \
    Cube.h \
    MathTasks.h \
    Pawn.h \
    Renderer.h \
    SceneComponent.h \
    Shader.h \
    VertexClasses.h \
    VisualFunction2D.h \
    VisualFunction3D.h \
    VisualObject.h \
    VisualPoints.h \
    XYZ.h \
    enums.h \
    functions.h \
    logger.h \
    mainwindow.h \
    renderwindow.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    fragment.frag \
    plainshader.frag \
    plainshader.vert \
    vertex.vert

