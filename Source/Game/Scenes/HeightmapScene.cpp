#include "HeightmapScene.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Engine/Actor.h"
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

HeightmapScene::HeightmapScene()
{
	WorldManager::GetInstance().SetWorld(this);

	//mSurface = new TriangleSurface(nullptr);
	//mSurface->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 80.f);

	auto t = new TriangleSurface(nullptr);
	t->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 80.f);
	mSurface = t;

	//mSurface = new TestMesh(nullptr, 4.f);
	mSurface->GenerateNormals();
	mSurface->Init();
	mSurface->bUseLighting = true;
	//surf->GenerateNeighbors();
	Actor* a = SpawnActor<Actor>("abc", mSurface);
	a->SetActorLocation(QVector3D());

	fCam = new FlyingCamera(QVector3D(0.f, 0.2f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	auto* cube = new Actor();
	cube->SetMesh(new CubeMesh(cube, 50.f, QVector3D(1.f, 0.f, 0.f), GL_LINES));
	mRenderer->Add("worldcube", cube);

	auto* xyz = new XYZ();
	mRenderer->Add("xyz", xyz);

	/*plane = new Plane(QVector3D(), 1.f, 1.f);
	mRenderer->Add("plane", plane);*/

	/*light = new Pawn();
	light->SetMesh(new LightCube(light, 0.5f, QVector3D(1.f, 1.f, 1.f)));
	light->SetActorLocation(QVector3D(0.f, 5.f, 0.f));
	mRenderer->Add("light", light);*/
	//light->SetAsCurrent();

	//auto* spring = new SpringArmComponent(light, 10.f, 45.f);
	//light->AddComponent(spring);
	//auto* scam = new CameraComponent(light);
	//scam->SetAsCurrent();
	//scam->bLookAtParent = true;
	//scam->SetFollowParent(false);
	//light->AddComponent(scam);
	//spring->SetCamera(scam);

	//reflectcube = new Actor();
	//reflectcube->SetMesh(new CubeMesh(reflectcube, 1.f, QVector3D(0.5f, 0.5f, 0.5f)));
	//mRenderer->Add("reflectcube", reflectcube);

	/*TestMesh* test = new TestMesh(nullptr, 1.f);
	test->GenerateNeighbors();*/

	auto* pl = new MeshWalker(QVector3D(0.f, 3.f, 0.f));
	mRenderer->Add("pl", pl);
	pl->SetAsCurrent();

	/*consolePrint("Bary: ", Math::Barycentric(
		QVector3D(1.2f, 0.f, 1.2f), 
		QVector3D(0,0,0), 
		QVector3D(3.f, 0.f, 1.f), 
		QVector3D(1.f, 0.f, 3.f)));*/
}

void HeightmapScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);
}
