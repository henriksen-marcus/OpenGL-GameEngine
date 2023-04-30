#include "CubemapScene.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Engine/Skybox.h"
#include "Source/Engine/Texture3D.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Game/XYZ.h"
#include "Source/Utility/Color.h"
#include "Source/Engine/CameraComponent.h"

CubemapScene::CubemapScene()
{
	WorldManager::GetInstance().SetWorld(this);

	std::vector<std::string> faces
	{
		"Assets/Textures/Skybox/field-skyboxes/FishPond/right.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/left.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/top.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/bottom.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/front.jpg",
		"Assets/Textures/Skybox/field-skyboxes/FishPond/back.jpg"
	};
	auto* skybox = new Skybox(new Texture3D(faces));
	mRenderer->SetSkybox(skybox);

	auto cross = new XYZ();
	mRenderer->Add("cross", cross);

	SetWorldColor({0.1f, 0.1f, 0.1f});
	//SetWorldColor(Color::Cyan);

	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);
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
}