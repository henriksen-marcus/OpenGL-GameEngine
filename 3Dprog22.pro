QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

FORMS += \
    Source/Engine/mainwindow.ui

HEADERS += \
    Source/Engine/Actor.h \
    Source/Engine/BaseObject.h \
    Source/Engine/Bezier.h \
    Source/Engine/Billboard.h \
    Source/Engine/Boundry2D.h \
    Source/Engine/CameraComponent.h \
    Source/Engine/CubicBezier.h \
    Source/Engine/CurveScene.h \
    Source/Engine/DebugLogger.h \
    Source/Engine/Math.h \
    Source/Engine/MeshComponent.h \
    Source/Engine/Meshes/ArrowMesh.h \
    Source/Engine/Meshes/CubeMesh.h \
    Source/Engine/Meshes/CylinderMesh.h \
    Source/Engine/Meshes/FlatTriangleMesh.h \
    Source/Engine/Meshes/LightCube.h \
    Source/Engine/Meshes/LineMesh.h \
    Source/Engine/Meshes/PlaneMesh.h \
    Source/Engine/Meshes/SphereMesh.h \
    Source/Engine/Meshes/TestMesh.h \
    Source/Engine/Meshes/TetrahedronMesh.h \
    Source/Engine/OBJMaterial.h \
    Source/Engine/Octree.h \
    Source/Engine/PausableTimer.h \
    Source/Engine/Pawn.h \
    Source/Engine/PlayerController.h \
    Source/Engine/QuadraticBezier.h \
    Source/Engine/Quadtree.h \
    Source/Engine/Renderer.h \
    Source/Engine/SceneComponent.h \
    Source/Engine/Shader.h \
    Source/Engine/Shader3.h \
    Source/Engine/ShaderManager.h \
    Source/Engine/Skybox.h \
    Source/Engine/SpringArmComponent.h \
    Source/Engine/Texture2D.h \
    Source/Engine/Texture3D.h \
    Source/Engine/TimeManager.h \
    Source/Engine/Timer.h \
    Source/Engine/TriangleSurface.h \
    Source/Engine/VertexClasses.h \
    Source/Engine/VisualObject.h \
    Source/Engine/World.h \
    Source/Engine/WorldManager.h \
    Source/Engine/ZigZag.h \
    Source/Engine/enums.h \
    Source/Engine/logger.h \
    Source/Engine/mainwindow.h \
    Source/Engine/renderwindow.h \
    Source/Engine/ui_mainwindow.h \
    Source/Game/Arrow.h \
    Source/Game/Axis.h \
    Source/Game/Camera.h \
    Source/Game/CubePlayer.h \
    Source/Game/Enemy.h \
    Source/Game/FlyingCamera.h \
    Source/Game/HealthPack.h \
    Source/Game/House.h \
    Source/Game/LightSwitch.h \
    Source/Game/LineActor.h \
    Source/Game/LineNPC.h \
    Source/Game/MeshWalker.h \
    Source/Game/Plane.h \
    Source/Game/Scenes/BarycentricScene.h \
    Source/Game/Scenes/CubemapScene.h \
    Source/Game/Scenes/CurveScene.h \
    Source/Game/Scenes/Eksamen2019Scene.h \
    Source/Game/Scenes/Eksamen2023Scene.h \
    Source/Game/Scenes/HeightmapScene.h \
    Source/Game/Scenes/Scene1.h \
    Source/Game/Scenes/TextureScene.h \
    Source/Game/StaticSceneCamera.h \
    Source/Game/TestCameraActor.h \
    Source/Game/VisualFunction2D.h \
    Source/Game/VisualPoints.h \
    Source/Game/XYZ.h \
    Source/Utility/Color.h \
    Source/Utility/MathTasks.h \
    Source/Utility/functions.h \
    Source/Engine/Texture.h \
    Vendor/stb_image.h

SOURCES += \
    Source/Engine/Actor.cpp \
    Source/Engine/BaseObject.cpp \
    Source/Engine/Bezier.cpp \
    Source/Engine/Billboard.cpp \
    Source/Engine/Boundry2D.cpp \
    Source/Engine/CameraComponent.cpp \
    Source/Engine/CubicBezier.cpp \
    Source/Engine/DebugLogger.cpp \
    Source/Engine/MeshComponent.cpp \
    Source/Engine/Meshes/PlaneMesh.cpp \
    Source/Engine/OBJMaterial.cpp \
    Source/Engine/Octree.cpp \
    Source/Engine/Pawn.cpp \
    Source/Engine/PlayerController.cpp \
    Source/Engine/QuadraticBezier.cpp \
    Source/Engine/Quadtree.cpp \
    Source/Engine/Renderer.cpp \
    Source/Engine/SceneComponent.cpp \
    Source/Engine/Shader.cpp \
    Source/Engine/Shader3.cpp \
    Source/Engine/Skybox.cpp \
    Source/Engine/SpringArmComponent.cpp \
    Source/Engine/Texture2D.cpp \
    Source/Engine/Texture3D.cpp \
    Source/Engine/TriangleSurface.cpp \
    Source/Engine/World.cpp \
    Source/Engine/logger.cpp \
    Source/Engine/mainwindow.cpp \
    Source/Engine/renderwindow.cpp \
    Source/Game/Arrow.cpp \
    Source/Game/Axis.cpp \
    Source/Game/CubePlayer.cpp \
    Source/Game/Enemy.cpp \
    Source/Game/FlyingCamera.cpp \
    Source/Game/HealthPack.cpp \
    Source/Game/House.cpp \
    Source/Game/LightSwitch.cpp \
    Source/Game/LineActor.cpp \
    Source/Game/LineNPC.cpp \
    Source/Game/MeshWalker.cpp \
    Source/Game/Plane.cpp \
    Source/Game/Scenes/BarycentricScene.cpp \
    Source/Game/Scenes/CubemapScene.cpp \
    Source/Game/Scenes/CurveScene.cpp \
    Source/Game/Scenes/Eksamen2019Scene.cpp \
    Source/Game/Scenes/Eksamen2023Scene.cpp \
    Source/Game/Scenes/HeightmapScene.cpp \
    Source/Game/Scenes/Scene1.cpp \
    Source/Game/Scenes/TextureScene.cpp \
    Source/Game/StaticSceneCamera.cpp \
    Source/Game/TestCameraActor.cpp \
    Source/Game/VisualFunction2D.cpp \
    Source/Game/VisualPoints.cpp \
    Source/Game/XYZ.cpp \
    Source/Engine/Texture.cpp \
    Vendor/stb_image.cpp \
    main.cpp

DISTFILES += \
    Source/Engine/Shader/fragment.frag \
    Source/Engine/Shader/phongshader.frag \
    Source/Engine/Shader/phongshader.vert \
    Source/Engine/Shader/plainshader.frag \
    Source/Engine/Shader/plainshader.vert \
    Source/Engine/Shader/texturefragshader.frag \
    Source/Engine/Shader/texturevertshader.vert \
    Source/Engine/Shader/vertex.vert



