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
#include "Source/Engine/Meshes/PlaneMesh.h"
#include "Source/Game/HealthPack.h"
#include "Source/Engine/QuadraticBezier.h"
#include "Source/Engine/Meshes/LineMesh.h"


BarycentricScene::BarycentricScene()
{
	WorldManager::GetInstance().SetWorld(this);

	/*auto* plane = new Plane(QVector3D(0.f, 10.f, 0.f), 2.f, 2.f);
	mRenderer->Add("plane", plane);
	plane->SetActorLocation(QVector3D(0.f, 4.5f, -15.f));
	plane->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));*/


	//Actor* ground = new Actor();
	//auto t = new TriangleSurface(ground);
	////t->FromImageFile("Assets/Heightmaps/Landscape2.jpg", 100.f, 50.f, 200.f);
	//t->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 100.f);
	////t->SetTexture("Assets/Textures/Landscape2.jpg");
	//t->GenerateNormals();
	//t->Init();
	//mSurface = t;
	//ground->SetMesh(mSurface);
	//ground->GetMesh()->mShaderName="god";
	//mRenderer->Add("ground", ground);
	//mSurface = ground->GetMesh();
	//mSurface->bUseLighting = true;
	//mSurface->SetFollowParent(false);

	//mWalker = new MeshWalker();
	//mWalker->SetAsCurrent();
	//mWalker->mSurface = mSurface;
	//mRenderer->Add("walker", mWalker);
	//mActors.push_back(mWalker);
	//mQuadtree->Insert(mWalker);

	auto cross = new XYZ();
	mRenderer->Add("cross", cross);

	/*m = new MeshComponent(nullptr);
	m->LoadFromOBJ("Assets/Meshes/CurvedSurface_flat.obj");
	m->Init();
	m->bUseLighting = true;
	m->SetFollowParent(false);

	SpawnActor<Actor>("cube", m);*/


	/*auto l = SpawnActor<Actor>("light", new LightCube(nullptr, 0.0001f));
	l->SetActorLocation(QVector3D(0.f, 5.f, 0.f));*/

	SetWorldColor(QVector3D(0.1f, 0.1f, 0.1f));

	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);

	temp = SpawnActor<Actor>("temp", new CubeMesh(nullptr, 0.2f));

	bez.AddSegment({{1,1,1}, {2,1,-1}, {3,0,0}});
	bez.AddSegment({{4,-1,1}, {5,-1,-1}, {6,0,0}});
	bez.AddSegment({{7,1,1}, {7,2,-1}, {6,3,0}});
	bez.mResolution = 100;
	bez.Init();
	bez.InitPoints();
	bez.bDrawPoints = true;
	bez.SetWorldLocation(QVector3D(5.f, -2.f, 0.f));

	SpawnActor<Actor>("curveactor", &bez);

	bez(0.2f);
}

void BarycentricScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);

	temp->SetActorLocation(bez(myt));

}