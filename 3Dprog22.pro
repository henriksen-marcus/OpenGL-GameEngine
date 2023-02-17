QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Actor.cpp \
    Cube.cpp \
    Shader.cpp \
    XYZ.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp

HEADERS += \
    Actor.h \
    Camera.h \
    Cube.h \
    Shader.h \
    VertexClasses.h \
    VisualObject.h \
    XYZ.h \
    enums.h \
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

#LIBS += -lOpenGL32
