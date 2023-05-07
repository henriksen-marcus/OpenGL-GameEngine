#include "TextureScene.h"
#include "Source/Game/Plane.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/Actor.h"
#include "Source/Game/XYZ.h"
#include "Source/Engine/PlayerController.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Engine/SpringArmComponent.h"
#include "Source/Engine/Pawn.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Game/LineActor.h"
#include "Source/Engine/Meshes/FlatTriangleMesh.h"
#include "Source/Game/FlyingCamera.h"

TextureScene::TextureScene()
{
    /*auto* plane = new Plane(QVector3D(), 5.f, 5.f);
    mActors.push_back(plane);
    mRenderer->Add("plane", plane);*/

    /*auto* cubeactor = new Actor();
    auto* cube = new CubeMesh(cubeactor, 0.5f);
    cube->SetTexture2D("../OpenGLMainQt/Textures/tex.jpg");
    cubeactor->SetMesh(cube);
    mActors.push_back(cubeactor);
    mRenderer->Add("cubeactor", cubeactor);*/

    auto* worldcube = new Actor();
    worldcube->SetMesh(new CubeMesh(worldcube, 50.f, QVector3D(1.f, 1.f, 1.f), GL_LINES));
    mActors.push_back(worldcube);
    mRenderer->Add("worldcube", worldcube);

    worldcube = new Actor();
    worldcube->SetMesh(new CubeMesh(worldcube, 50.f, QVector3D(1.f, 1.f, 1.f), GL_LINES));
    mActors.push_back(worldcube);
    mRenderer->Add("worldcube2", worldcube);
    worldcube->AddActorLocalRotation(QVector3D(0.f, 0.f, 45.f));
    worldcube->SetActorScale(QVector3D(0.75f, 0.75f, 1.f));



    auto* a = new Actor(QVector3D(5.f, 0.f, 0.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(1.f, 0.f, 0.f)));
    mRenderer->Add("1", a);

    a = new Actor(QVector3D(-5.f, 0.f, 0.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(0.5f, 0.f, 0.f)));
    mRenderer->Add("2", a);

    a = new Actor(QVector3D(0.f, 5.f, 0.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(0.f, 1.f, 0.f)));
    mRenderer->Add("3", a);

    a = new Actor(QVector3D(0.f, -5.f, 0.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(0.f, 0.5f, 0.f)));
    mRenderer->Add("4", a);

    a = new Actor(QVector3D(0.f, 0.f, 5.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(0.f, 0.f, 1.f)));
    mRenderer->Add("5", a);

    a = new Actor(QVector3D(0.f, 0.f, -5.f));
    a->SetMesh(new CubeMesh(a, 1.f, QVector3D(0.f, 0.f, 0.5f)));
    mRenderer->Add("6", a);



    /*auto* camActor = new Actor(QVector3D(0.f, 8.f, 0.f));
    auto* cam = new CameraComponent(camActor);
    cam->mFOV = 60.f;
    cam->SetPitch(-89.f);
    camActor->AddComponent(cam);
    mActors.push_back(camActor);
    mRenderer->Add("camActor", camActor);
    camActor->name = "camActor";*/

    //PlayerController::GetInstance().SetCurrentCamera(cam);

    /*myactor = new Actor();
    myactor->SetMesh(new FlatTriangleMesh(myactor));
    mRenderer->Add("dasdsadsa", myactor);
    myactor->GetMesh()->SetFollowParent(false);
    x = new LineActor(QVector3D(1.f, 0.f, 0.f));
    mRenderer->Add("dadsadddddddddddd", x);*/

 //   player = new Pawn(QVector3D(0.f, 0.f, 0.f));
 //   player->SetMesh(new CubeMesh(player, 0.2f));
 //   mActors.push_back(player);
 //   mRenderer->Add("player", player);
 //   PlayerController::GetInstance().SetCurrentPossessed(player);

 //   x = new LineActor(QVector3D(1.f, 0.f, 0.f));
 //   y = new LineActor(QVector3D(0.f, 1.f, 0.f));
 //   //z = new LineActor(QVector3D(1.f, 0.5f, 1.f));
 //   mRenderer->Add("x", x);
 //   mRenderer->Add("y", y);
 //   //mRenderer->Add("z", z);

 //   Cam = new CameraComponent(player);
 //   Cam->SetFollowParent(false);
	//Cam->SetPitch(-25.f);
 //   Cam->bLookAtParent = true;
 //   player->AddComponent(Cam);
 //   //PlayerController::GetInstance().SetCurrentCamera(Cam);

 //   auto* Springarm = new SpringArmComponent(player, 3.f, 45.f);
 //   Springarm->SetAttachment(Cam);
 //   Springarm->SetFollowParent(true);
 //   player->AddComponent(Springarm);

    /*auto a = QQuaternion::fromEulerAngles(QVector3D(0.f, 0.f, 0.f));
    auto b = QQuaternion::fromEulerAngles(QVector3D(0.f, 20.f, 0.f)) * a;
    x->Update(QVector3D(), a.rotatedVector(QVector3D(0.f, 0.f, -1.f)));
    y->Update(QVector3D(), b.rotatedVector(QVector3D(0.f, 0.f, -1.f)));*/

    cross = new XYZ();
    cross->Init();
    mActors.push_back(cross);
    mRenderer->Add("cross", cross);

    auto* fcam = new FlyingCamera(QVector3D(0.f, 0.5f, 3.f));
    fcam->SetAsCurrent();
    fcam->GetCamera()->SetAsCurrent();
    mRenderer->Add("fcam", fcam);
}

void TextureScene::Tick(float deltaTime)
{
    World::Tick(deltaTime);
    /*auto m = myactor->GetMesh();
    m->AddWorldRotation(QQuaternion::fromEulerAngles(QVector3D(0.f, 0.1f, 0.f)));
    m->AddWorldOffset(m->GetWorldRotation().rotatedVector(QVector3D(0.f, 0.f, -1.f)) * 0.005f);*/
}
