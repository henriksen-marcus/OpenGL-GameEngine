QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Actor.cpp \
    Arrow.cpp \
    Axis.cpp \
    BaseObject.cpp \
    Boundry2D.cpp \
    CameraComponent.cpp \
    Cube.cpp \
    CubePlayer.cpp \
    HealthPack.cpp \
    House.cpp \
    LineNPC.cpp \
    Octree.cpp \
    Pawn.cpp \
    Plane.cpp \
    PlayerController.cpp \
    Quadtree.cpp \
    Scene1.cpp \
    SceneComponent.cpp \
    Shader.cpp \
    StaticSceneCamera.cpp \
    VisualFunction2D.cpp \
    VisualFunction3D.cpp \
    World.cpp \
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
    Boundry2D.h \
    Camera.h \
    CameraComponent.h \
    Cube.h \
    CubePlayer.h \
    HealthPack.h \
    House.h \
    LineNPC.h \
    MathTasks.h \
    Octree.h \
    PausableTimer.h \
    Pawn.h \
    Plane.h \
    PlayerController.h \
    Quadtree.h \
    Renderer.h \
    Scene1.h \
    SceneComponent.h \
    Shader.h \
    StaticSceneCamera.h \
    TimeManager.h \
    VertexClasses.h \
    VisualFunction2D.h \
    VisualFunction3D.h \
    VisualObject.h \
    VisualPoints.h \
    World.h \
    WorldManager.h \
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

