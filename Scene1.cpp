#include "Scene1.h"
#include "Plane.h"
#include "Cube.h"
#include "CubePlayer.h"
#include "HealthPack.h"
#include "XYZ.h"
#include "PlayerController.h"
#include "StaticSceneCamera.h"

Scene1::Scene1()
{
    ground = new Plane(QVector3D(0.f, -0.21f, 0.f), 10.f, 5.f, QVector3D(150, 111, 51));
    bigCube = new Cube(QVector3D(), 20.f, QVector3D(1.f, 1.f, 1.f), GL_LINES, true);
    cross = new XYZ(true);
    player = new CubePlayer();
    //pack1 = new HealthPack(QVector3D(-2.f, 0.f, 0.f));
    sceneCamera = new StaticSceneCamera();

    PlayerController::GetInstance().SetCurrentPossessed(player);
    PlayerController::GetInstance().SetCurrentCamera(sceneCamera->GetCurrentCamera());

    mActors.push_back(ground);
    mActors.push_back(bigCube);
    mActors.push_back(cross);
    mActors.push_back(player);
//    mActors.push_back(pack1);

    mRenderer->Add("ground", ground);
    mRenderer->Add("bigCube", bigCube);
    mRenderer->Add("cross", cross);
    mRenderer->Add("player", player);
//    mRenderer->Add("pack1", pack1);
}

void Scene1::Tick(float deltaTime, GLint mModelLocation)
{
    World::Tick(deltaTime, mModelLocation);
    sceneCamera->Tick(deltaTime);
}
