#include "TextureScene.h"
#include "Plane.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "XYZ.h"
#include "PlayerController.h"
#include "Meshes/CubeMesh.h"
#include "SpringArmComponent.h"
#include "Pawn.h"
#include "Meshes/CubeMesh.h"
#include "LineActor.h"

TextureScene::TextureScene()
{
    /*auto* plane = new Plane(QVector3D(), 5.f, 5.f);
    mActors.push_back(plane);
    mRenderer->Add("plane", plane);*/

    /*auto* cubeactor = new Actor();
    auto* cube = new CubeMesh(cubeactor, 0.5f);
    cube->SetTexture("../OpenGLMainQt/Textures/tex.jpg");
    cubeactor->SetMesh(cube);
    mActors.push_back(cubeactor);
    mRenderer->Add("cubeactor", cubeactor);*/

    auto* camActor = new Actor(QVector3D(0.f, 2.f, 3.f));
    auto* cam = new CameraComponent(camActor);
    cam->mFOV = 75.f;
    cam->mPitch = -25.f;
    camActor->AddComponent(cam);
    mActors.push_back(camActor);
    mRenderer->Add("camActor", camActor);
    camActor->name = "camActor";

    PlayerController::GetInstance().SetCurrentCamera(cam);

    //auto* player = new Pawn(QVector3D(0.f, 0.5f, 0.f));
    //player->SetMesh(new CubeMesh(player, 0.2f));
    //auto* Springarm = new SpringArmComponent(player, 1.f, 45.f);
    //auto* Cam = new CameraComponent(player);
    //Cam->followParentRotation = false;
    //Cam->followParentTransform = false;
    //Springarm->SetCameraComponent(Cam);
    //player->AddComponent(Springarm);
    //mActors.push_back(player);
    //mRenderer->Add("player", player);
    ////PlayerController::GetInstance().SetCurrentCamera(Cam);
    //player->SetActor(player);
    //PlayerController::GetInstance().SetCurrentPossessed(player);

    cross = new XYZ();
    cross->Init();
    mActors.push_back(cross);
    mRenderer->Add("cross", cross);

    /*auto* cubeactor = new Pawn(QVector3D(0.f, 0.5f, 0.f));
    cubeactor->SetMesh(new CubeMesh(cubeactor, 0.2f, QVector3D(1.f, 0.f, 0.f)));
    mActors.push_back(cubeactor);
    mRenderer->Add("cubeactor", cubeactor);
    PlayerController::GetInstance().SetCurrentPossessed(cubeactor);*/

    /*auto* c1 = new Actor(QVector3D(-1.f, 1.f, 0.f));
    c1->SetMesh(new CubeMesh(c1, 0.1f, QVector3D(0.f, 1.f, 0.f)));
    mActors.push_back(c1);
    mRenderer->Add("c1", c1);
    auto* c2 = new Actor();
    c2->SetMesh(new CubeMesh(c2, 0.1f, QVector3D(0.f, 0.f, 1.f)));
    mActors.push_back(c2);
    mRenderer->Add("c2", c2);*/

    l1 = new LineActor();
    mActors.push_back(l1);
    //mRenderer->Add("l1", l1);
    //l1->SetActorScale(QVector3D(4.f, 4.f, 4.f));
    //l1->Update(c1->GetActorLocation(), c2->GetActorLocation());

    mycube = new Actor();
    mycube->SetMesh(new CubeMesh(mycube, 1.f));
    mRenderer->Add("mycube", mycube);
}

void TextureScene::Tick(float deltaTime)
{
    World::Tick(deltaTime);
    //mycube->AddActorLocalScale(QVector3D(0.2f, 0.2f, 0.f));
    mycube->AddActorLocalRotation(QVector3D(5.f, 1.f, 0.5f));
    //l1->AddActorLocalRotation(QVector3D(0.f, 0.5f, 0.f));
    //l1->GetMesh()->AddWorldRotation(QQuaternion::fromEulerAngles(QVector3D(0.1f, 0.1f, 1.f)));
    //mRenderer->Get("cross")->AddActorLocalOffset(QVector3D(0.f, 0.f, -0.05f));
}
