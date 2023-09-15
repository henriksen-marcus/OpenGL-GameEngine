#include "Eksamen2023Scene.h"
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
#include "Source/Engine/Meshes/PlaneMesh.h"
#include "Source/Game/HealthPack.h"
#include "Source/Engine/QuadraticBezier.h"
#include "Source/Engine/Texture3D.h"
#include "Source/Engine/Meshes/LineMesh.h"
#include "Source/Utility/Color.h"
#include "Source/Engine/Skybox.h"
#include "Source/Engine/QuadraticBezier.h"
#include "Source/Engine/CubicBezier.h"
#include "Source/Game/Enemy.h"
#include "Source/Game/LightSwitch.h"

Eksamen2023Scene::Eksamen2023Scene()
{
	WorldManager::GetInstance().SetWorld(this);
	mapName = "Eksamen2023Scene";

	// Axis cross
	SpawnXYZ();

	// Player (Task 1, 4)
	mWalker = new MeshWalker();
	mWalker->SetAsCurrent();
	mWalker->mSurface = mSurface;
	mRenderer->Add("walker", mWalker);
	mActors.push_back(mWalker);
	mQuadtree->Insert(mWalker);

	// Plane with texture (Task 2)
	texturePlane = new Plane(QVector3D(0.f, 10.f, 0.f), 2.f, 2.f);
	mRenderer->Add("plane", texturePlane);
	texturePlane->SetActorLocation(QVector3D(0.f, 4.5f, -15.f));
	texturePlane->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

	// Heightmap (Task 3)
	auto t = new TriangleSurface(mSurfaceActor);
	//t->FromImageFile("Assets/Heightmaps/Landscape2.jpg", 100.f, 50.f, 200.f);
	t->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 100.f);
	//t->SetTexture2D("Assets/Textures/Landscape2.jpg");
	t->GenerateNormals();
	t->Init();
	mSurface = t;

	mSurfaceActor = new Actor();
	mSurfaceActor->SetMesh(mSurface);
	mSurfaceActor->GetMesh()->mShaderName="god";
	mRenderer->Add("ground", mSurfaceActor);
	mSurface->bUseLighting = true;
	mSurface->SetFollowParent(false);

	trophy = new HealthPack(QVector3D(-4.f, 2.3f, -10.f));
	mRenderer->Add("trophy", trophy);
	mActors.push_back(trophy);

	enemy = new Enemy(QVector3D(4.f, 2.2f, -10.f));
	mRenderer->Add("enemy", enemy);
	mActors.push_back(enemy);
	//mQuadtree->Insert(enemy);

	lightSwitch = new LightSwitch((QVector3D(0.f, 2.3f, -7.f)));
	mRenderer->Add("lightSwitch", lightSwitch);
	mActors.push_back(lightSwitch);
	

	auto* m = new MeshComponent(nullptr);
	m->LoadFromOBJ("Assets/Meshes/monkey.obj");
	m->GenerateNormals();
	m->Init();
	m->bUseLighting = true;
	SpawnActor<Actor>("monkey", m)->SetActorLocation({ 0.f, 4.f, -10.f });

	// GlClearColor color
	SetWorldColor(Color::Cyan);

	// Skybox
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

	mPlayerStart.location = { 0, 0, 5 };
}

Eksamen2023Scene::~Eksamen2023Scene()
{
}

void Eksamen2023Scene::AddScore()
{
	playerScore++;
	print("Point added! Score: " + std::to_string(playerScore));
	cPrint("Point added! Score: " + std::to_string(playerScore));
}

void Eksamen2023Scene::BeginPlay()
{
	World::BeginPlay();
	mWalker->SetActorLocation(mPlayerStart.location);
	mWalker->SetActorRotation(mPlayerStart.rotation);
}

void Eksamen2023Scene::Tick(float deltaTime)
{
	World::Tick(deltaTime);
}

void Eksamen2023Scene::RestartGame()
{
	mWalker->SetActorLocation(mPlayerStart.location);
	mWalker->SetActorRotation(mPlayerStart.rotation);
	mWalker->OnGameReset();

	RemoveActor(trophy);
	trophy = new HealthPack(QVector3D(-4.f, 2.3f, -10.f));
	mRenderer->Add("trophy", trophy);
	mActors.push_back(trophy);

	RemoveActor(enemy);
	enemy = new Enemy(QVector3D(4.f, 2.2f, -10.f));
	mRenderer->Add("enemy", enemy);
	mActors.push_back(enemy);

	playerScore = 0;

	World::RestartGame();
}
