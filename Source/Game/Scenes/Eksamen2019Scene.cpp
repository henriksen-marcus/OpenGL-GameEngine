#include "Eksamen2019Scene.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Engine/CameraComponent.h"

Eksamen2019Scene::Eksamen2019Scene()
{
	WorldManager::GetInstance().SetWorld(this);

	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	SpawnXYZ();

	auto* surface = new TriangleSurface(nullptr);
	//surface->FromFlat(-4, 4, -3, 3, 2, 2);
	surface->FromFlat(0,1, 0, 1, 1, 1);
	surface->GenerateNormals();
	surface->Init();
	auto* surfaceActor = SpawnActor("surface", surface);

	auto* mesh = new TriangleSurface(nullptr);
	mesh->FromTextFileIndices("surface.txt");
	mesh->Init();
	SpawnActor("mesh", mesh)->AddActorLocalOffset({0.f, 5.f, 0.f});

	//surface->ToTextFileIndices("surface.txt");
}

Eksamen2019Scene::~Eksamen2019Scene()
{
}

void Eksamen2019Scene::BeginPlay()
{
}

void Eksamen2019Scene::Tick(float deltaTime)
{
	World::Tick(deltaTime);

}