#include "PresentationWorld.h"
#include "Source/Engine/Actor.h"
#include "Source/Game/XYZ.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Engine/Skybox.h"
#include "Source/Engine/Texture3D.h"
#include "Source/Engine/Meshes/LightCube.h"

PresentationWorld::PresentationWorld()
{
	WorldManager::GetInstance().SetWorld(this);

	auto tempmesh = new MeshComponent(nullptr);
	tempmesh->LoadFromOBJ("Assets/Meshes/monkey_high.obj");
	tempmesh->Init();
	tempmesh->bUseLighting = true;
	mMesh = SpawnActor("mMesh", tempmesh);
	SetWorldColor({ 0.1f, 0.1f, 0.1f });

	auto fCam = new FlyingCamera(QVector3D(0.f, 0.f, 5.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	mLightCube = new LightCube(nullptr, 0.05f);
	mLightCube->activateLight = true;
	mLightCube->bFollowParentTransform = true;

	mLight = new Actor(QVector3D(0, 10, 10));
	mLight->AddComponent(mLightCube);
	mRenderer->Add("light", mLight);
}

void PresentationWorld::BeginPlay()
{

}

void PresentationWorld::Tick(float deltaTime)
{
	World::Tick(deltaTime);
	mLightCube->Draw();

	mMesh->AddActorLocalRotation({ 0, 60*deltaTime, 0 });
}
