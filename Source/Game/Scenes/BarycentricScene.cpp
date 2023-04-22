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


BarycentricScene::BarycentricScene()
{
	WorldManager::GetInstance().SetWorld(this);

	/*auto* plane = new Plane(QVector3D(0.f, 10.f, 0.f), 2.f, 2.f);
	mRenderer->Add("plane", plane);
	plane->SetActorLocation(QVector3D(0.f, 4.5f, -15.f));
	plane->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));*/

	std::function<float(float, float)> f = [](float a, float b) -> float {
		return atan(sin(a)+(b/2))/2;
	};

	//Actor* ground = new Actor();
	//auto t = new TriangleSurface(ground);
	//t->FromFunction(f, -10, 10, -10, 10, 50);
	////t->FromImageFile("Assets/Heightmaps/Landscape2.jpg", 100.f, 50.f, 200.f);
	////t->FromImageFile("Assets/Heightmaps/Heightmap8.jpg", 40.f, 2.f, 100.f);
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

	/*auto* hp = new HealthPack(QVector3D(0.f, 2.5f, -10.f));
	mRenderer->Add("hp", hp);
	mActors.push_back(hp);
	mQuadtree->Insert(hp);
	*/

	auto cross = new XYZ();
	mRenderer->Add("cross", cross);
	cross->SetActorScale(QVector3D(3.f, 3.f, 3.f));

	m = new MeshComponent(nullptr);
	m->LoadFromOBJ("Assets/Meshes/artcube.obj");
	m->Init();
	m->bUseLighting = true;
	m->SetFollowParent(false);

	SpawnActor<Actor>("cube", m);


	auto l = SpawnActor<Actor>("light", new LightCube(nullptr, 0.0001f));
	l->SetActorLocation(QVector3D(0.f, 5.f, 0.f));


	auto fCam = new FlyingCamera(QVector3D(0.f, 2.f, 2.f));
	fCam->SetAsCurrent();
	fCam->GetCamera()->SetAsCurrent();
	mRenderer->Add("fcam", fCam);
}

void BarycentricScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);

	m->mShaderName = "god";
	m->Draw();
	m->mShaderName = "geo";
	m->Draw();

	//m->AddWorldOffset(QVector3D(0.02f, 0.f, 0.f));
	//m->AddWorldRotation(QVector3D(0.2f, 0.f, 0.1f));
}
