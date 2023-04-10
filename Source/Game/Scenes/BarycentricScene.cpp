#include "BarycentricScene.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Engine/Actor.h"
#include "Source/Engine/mainwindow.h"
#include "Source/Engine/PlayerController.h"
#include "Source/Game/XYZ.h"
#include "Source/Game/Plane.h"
#include "Source/Engine/Meshes/LightCube.h"
#include "Source/Engine/Meshes/FlatTriangleMesh.h"
#include "Source/Engine/SpringArmComponent.h"
#include "Source/Engine/Meshes/ArrowMesh.h"
#include "Source/Engine/Meshes/TestMesh.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Game/MeshWalker.h"
#include "Source/Engine/Math.h"
#include "Source/Engine/Quadtree.h"
#include "Source/Engine/Timer.h"
#include "Source/Game/HealthPack.h"


BarycentricScene::BarycentricScene()
{
	WorldManager::GetInstance().SetWorld(this);

	auto* plane = new Plane(QVector3D(0.f, 10.f, 0.f), 2.f, 2.f);
	mRenderer->Add("plane", plane);
	plane->SetActorLocation(QVector3D(0.f, 4.5f, -15.f));
	plane->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

	Actor* ground = new Actor();
	auto t = new TriangleSurface(ground);
	//t->FromImageFile("Assets/Heightmaps/Landscape2.jpg", 100.f, 50.f, 200.f);
	t->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 100.f);
	//t->SetTexture("Assets/Textures/Landscape2.jpg");
	t->GenerateNormals();
	t->Init();
	mSurface = t;
	ground->SetMesh(mSurface);
	ground->GetMesh()->mShaderName="god";
	mRenderer->Add("ground", ground);
	mSurface = ground->GetMesh();
	mSurface->bUseLighting = true;

	mWalker = new MeshWalker();
	mWalker->SetAsCurrent();
	mWalker->mSurface = mSurface;
	mRenderer->Add("walker", mWalker);
	mActors.push_back(mWalker);
	mQuadtree->Insert(mWalker);

	auto* hp = new HealthPack(QVector3D(0.f, 2.5f, -10.f));
	mRenderer->Add("hp", hp);
	mActors.push_back(hp);
	mQuadtree->Insert(hp);

	/*auto l = SpawnActor<Actor>("light", new LightCube(nullptr, 0.0001f));
	l->SetActorLocation(QVector3D(0.f, 5.f, 0.f));*/

	/*auto* fc = new FlyingCamera(QVector3D(0.f, 5.f, 2.f));
	fc->SetAsCurrent();
	fc->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fc);*/
}

void BarycentricScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);
}
