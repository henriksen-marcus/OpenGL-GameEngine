#include "TestCameraActor.h"
#include "Source/Engine/SpringArmComponent.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Engine/CameraComponent.h"

TestCameraActor::TestCameraActor()
{
	mMesh = new CubeMesh(static_cast<Actor*>(this), 0.2f);
	camVis = new CubeMesh(static_cast<Actor*>(this), 0.2f, QVector3D(1.f, 0.f, 0.f));
	mComponents.push_back(camVis);
	camVis->SetFollowParent(false);
	springArm = new SpringArmComponent(static_cast<Actor*>(this), 1.f, 45.f);
	camera = new CameraComponent(static_cast<Actor*>(this));
	camera->SetFollowParent(false);
	springArm->SetAttachment(camera);
}

void TestCameraActor::Draw()
{
	Pawn::Draw();
	camVis->Draw();
}

void TestCameraActor::Tick(float deltaTime)
{
	Pawn::Tick(deltaTime);
	camVis->SetWorldLocation(camera->GetWorldLocation());
}
