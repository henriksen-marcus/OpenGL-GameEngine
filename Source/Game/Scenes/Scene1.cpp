#include "Scene1.h"
#include "Source/Game/Plane.h"
#include "Source/Game/CubePlayer.h"
#include "Source/Game/HealthPack.h"
#include "Source/Game/XYZ.h"
#include "Source/Engine/PlayerController.h"
#include "Source/Game/StaticSceneCamera.h"
#include "Source/Game/LineNPC.h"
#include "Source/Engine/Quadtree.h"
#include "Source/Game/House.h"
#include "Source/Game/Arrow.h"

Scene1::Scene1()
{
    ground = new Plane(QVector3D(0.f, -0.21f, 0.f), 8.f, 5.5f, QVector3D(150.f/255.f, 111.f/255.f, 51.f/255.f));
    //bigCube = new Cube(QVector3D(), 20.f, QVector3D(1.f, 1.f, 1.f), GL_LINES, true);
    cross = new XYZ();
    player = new CubePlayer();
    player->name = "Mainplayer";
    sceneCamera = new StaticSceneCamera();
    auto* house = new House(QVector3D(0.f, 0.25f, -2.f));
    house->mainCam = sceneCamera->camera1;
    house->houseCam = sceneCamera->camera2;

    auto* arrow = new Arrow(QVector3D(0.f, 0.3f, -2.f), 0.2f, QVector3D(1.f, 0.f, 0.f), QVector3D(1.f, 0.f, 1.f));

    auto f1 = [](float x) -> float { return sin(x); };
    auto f2 = [](float x) -> float { return log(x); };
    lineNPC = new LineNPC(f1, f2, 0.f, 3.f, 25);
    lineNPC->Init();
    lineNPC->SetActorLocation(QVector3D(-5.f, 1.2f, -1.f));

    GetPlayerController().SetCurrentPossessed(player);
    GetPlayerController().SetCurrentCamera(sceneCamera->GetCurrentCamera());

    mActors.push_back(ground);
    //mActors.push_back(bigCube);
    mActors.push_back(cross);
    mActors.push_back(player);
    mActors.push_back(lineNPC);
    mActors.push_back(house);
    mActors.push_back(arrow);

    mRenderer->Add("ground", ground);
    //mRenderer->Add("bigCube", bigCube);
    mRenderer->Add("cross", cross);
    mRenderer->Add("player", player);
    mRenderer->Add("lineNPC", lineNPC);
    mRenderer->Add("house", house);
    mRenderer->Add("arrow", arrow);

    mQuadtree->Insert(player);
    mQuadtree->Insert(house);
    //mQuadtree->Init();

    healthpacks.push_back(new HealthPack(QVector3D(-2.f, 0.f, -2.f)));
    healthpacks.push_back(new HealthPack(QVector3D(-1.f, 0.f, -1.f)));
    healthpacks.push_back(new HealthPack(QVector3D(-3.f, 0.f, -1.f)));
    healthpacks.push_back(new HealthPack(QVector3D(2.f, 0.f, 1.f)));
    healthpacks.push_back(new HealthPack(QVector3D(3.f, 0.f, -2.5f)));
    healthpacks.push_back(new HealthPack(QVector3D(2.5f, 0.f, -1.f)));

    int i = 0;
    std::string name = "hPack";
    for (auto p : healthpacks)
    {
        mActors.push_back(p);
        mQuadtree->Insert(p);
        mRenderer->Add(name + std::to_string(i++), p);
    }

}

void Scene1::Tick(float deltaTime)
{
    World::Tick(deltaTime);
    sceneCamera->Tick(deltaTime);
}
