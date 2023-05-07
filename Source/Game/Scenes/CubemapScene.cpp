#include "CubemapScene.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Engine/Skybox.h"
#include "Source/Engine/Texture3D.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Game/XYZ.h"
#include "Source/Utility/Color.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Engine/Actor.h"
#include "Source/Engine/Math.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Engine/Meshes/CylinderMesh.h"
#include "Source/Engine/PlayerController.h"
#include "Source/Engine/Texture2D.h"
#include "Source/Engine/Meshes/PlaneMesh.h"
#include "Source/Engine/Meshes/TetrahedronMesh.h"
#include "Source/Game/Plane.h"

CubemapScene::CubemapScene()
{
	WorldManager::GetInstance().SetWorld(this);

	/*std::vector<std::string> faces
	{
		"Assets/Textures/Skybox/field-skyboxes/FishPond/right.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/left.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/top.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/bottom.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/front.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/back.jpg"
	};
	auto* skybox = new Skybox(new Texture3D(faces));
	mRenderer->SetSkybox(skybox);*/

	auto cross = new XYZ();
	mRenderer->Add("cross", cross);

	SetWorldColor({0.1f, 0.1f, 0.1f});
	//SetWorldColor(Color::Cyan);

	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	/*auto t = new TriangleSurface(nullptr);
	t->FromFlat(0.f, 1.f, 0.f, 1.f, 0.5f, 0.5f);
	t->Init();
	SpawnActor("t", t);*/

	auto billboard = new Billboard(nullptr, 0.5f, 0.5f);
	billboard->SetTexture2D(new Texture2D("Assets/Textures/wall.jpg"));
	billboard->Init();
	SpawnActor("bill", billboard);

	/*auto p = new PlaneMesh(nullptr, 1.f, 1.f);
	p->SetTexture2D(new Texture2D("Assets/Textures/wall.jpg"));
	mesh = new Actor();
	mesh->SetMesh(p);
	mRenderer->Add("planedsadsadsa", mesh);
	mesh->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));*/
}

CubemapScene::~CubemapScene()
{
}

void CubemapScene::BeginPlay()
{
}

void CubemapScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);

	/*auto cam = PlayerController::GetInstance().GetCurrentCamera();
	auto target = cam->GetWorldLocation();
	target += cam->GetForwardVector() * 2.f;
	auto pos = Math::VInterpTo(mesh->GetActorLocation(), target, deltaTime, 5.f);
	mesh->SetActorLocation(pos);*/
}