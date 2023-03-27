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
    CubePlayer.cpp \
    HealthPack.cpp \
    House.cpp \
    LineNPC.cpp \
    MeshComponent.cpp \
    Meshes/PlaneMesh.cpp \
    Octree.cpp \
    Pawn.cpp \
    Plane.cpp \
    PlayerController.cpp \
    Quadtree.cpp \
    Scene1.cpp \
    SceneComponent.cpp \
    Shader.cpp \
    StaticSceneCamera.cpp \
    Texture2D.cpp \
    TextureScene.cpp \
    Vendor/stb_image.cpp \
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
    CubePlayer.h \
    HealthPack.h \
    House.h \
    LineNPC.h \
    MathTasks.h \
    MeshComponent.h \
    Meshes/CubeMesh.h \
    Meshes/PlaneMesh.h \
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
    ShaderManager.h \
    StaticSceneCamera.h \
    Texture2D.h \
    TextureScene.h \
    TimeManager.h \
    Vendor/stb_image.h \
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
    phongshader.frag \
    phongshader.vert \
    plainshader.frag \
    plainshader.vert \
    texturefragshader.frag \
    texturevertshader.vert \
    vertex.vert

