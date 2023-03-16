#include "TextureScene.h"
#include "Plane.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "XYZ.h"
#include "PlayerController.h"

TextureScene::TextureScene()
{
    auto* plane = new Plane(QVector3D(), 5.f, 5.f);
    mActors.push_back(plane);
    mRenderer->Add("plane", plane);

    auto* camActor = new Actor(QVector3D(0.f, 1.f, 2.f));
    auto* cam = new CameraComponent(camActor);
    cam->mFOV = 80.f;
    cam->mPitch = -15.f;
    camActor->AddComponent(cam);
    mActors.push_back(camActor);
    mRenderer->Add("camActor", camActor);
    camActor->name = "camActor";

    PlayerController::GetInstance().SetCurrentCamera(cam);

    auto* cross = new XYZ();
    cross->Init();
    mActors.push_back(cross);
    mRenderer->Add("cross", cross);
}

void TextureScene::Tick(float deltaTime)
{
    World::Tick(deltaTime);

    //mRenderer->Get("cross")->AddActorLocalOffset(QVector3D(0.f, 0.f, -0.05f));
}
