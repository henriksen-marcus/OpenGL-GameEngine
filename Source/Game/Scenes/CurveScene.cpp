#include "CurveScene.h"
#include "Source/Engine/WorldManager.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Game/FlyingCamera.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Game/XYZ.h"

CurveScene::CurveScene()
{
	WorldManager::GetInstance().SetWorld(this);

	auto cross = new XYZ();
	mRenderer->Add("cross", cross);

	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	curveCube = SpawnActor<Actor>("curveCube", new CubeMesh(nullptr, 0.2f));

	bez.AddSegment({{1,1,1}, {2,1,-1}, {3,0,0}});
	bez.AddSegment({{4,-1,1}, {5,-1,-1}, {6,0,0}});
	bez.AddSegment({{7,1,1}, {7,2,-1}, {6,3,0}});
	bez.mResolution = 100;
	bez.Init();
	bez.InitPoints();
	bez.bDrawPoints = true;

	SpawnActor<Actor>("bez", &bez);
}

CurveScene::~CurveScene()
{
}

void CurveScene::BeginPlay()
{
}

void CurveScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);
	curveCube->SetActorLocation(bez(zig()));
}