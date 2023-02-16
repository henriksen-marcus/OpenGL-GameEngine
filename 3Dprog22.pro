QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    shader.cpp

HEADERS += \
    VertexClasses.h \
    VisualObject.h \
    logger.h \
    mainwindow.h \
    renderwindow.h \
    shader.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    fragment.frag \
    plainshader.frag \
    plainshader.vert \
    vertex.vert

LIBS += -lopengl32
