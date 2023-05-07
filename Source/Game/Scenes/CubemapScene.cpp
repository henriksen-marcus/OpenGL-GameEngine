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
#include "Source/Engine/Meshes/PlaneMesh.h"
#include "Source/Engine/Meshes/TetrahedronMesh.h"

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

	/*auto t = new TriangleSurface(nullptr);
	t->FromFlat(0.f, 1.f, 0.f, 1.f, 0.5f, 0.5f);
	t->Init();
	SpawnActor("t", t);*/

	plane = SpawnActor("p", new PlaneMesh(nullptr, 1.f, 1.f));
}

CubemapScene::~CubemapScene()
{
}

void CubemapScene::BeginPlay()
{
	/*billboard = new Billboard(nullptr, 0.5f, 0.5f);

	bActor = SpawnActor("b", billboard);
	bActor->GetMesh()->SetFollowParent(true);*/
}

void CubemapScene::Tick(float deltaTime)
{
	World::Tick(deltaTime);

	auto cam = PlayerController::GetInstance().GetCurrentCamera();
	auto target = cam->GetWorldLocation();/*
	target += cam->GetForwardVector() * 2.f;

	auto pos = Math::VInterpTo(mesh->GetActorLocation(), target, deltaTime, 5.f);
	mesh->SetActorLocation(pos);*/


	auto dirFromCam = plane->GetActorLocation() - cam->GetWorldLocation();
	dirFromCam.normalize();


	QVector3D upVector(0, 1, 0); // Assuming up is always in the positive y direction
	if (qAbs(QVector3D::dotProduct(dirFromCam, upVector)) < 0.99) // Check if the direction is not parallel to up/down
	{
	    // Calculate a vector perpendicular to both the direction vector and the up vector
	    QVector3D xaxis = QVector3D::crossProduct(upVector, dirFromCam).normalized();
	    // Calculate the plane's new local Y-axis as the cross product of the new local X-axis and the direction vector
	    QVector3D yaxis = QVector3D::crossProduct(xaxis, dirFromCam).normalized();
	    // Calculate the rotation quaternion that aligns the plane's local Z-axis with the direction vector
	    QQuaternion rotation = QQuaternion::fromAxes(xaxis, yaxis, dirFromCam);
	    plane->SetActorRotation(rotation);
	}

	/*auto r = QQuaternion::rotationTo(QVector3D(0,-1,0), dirFromCam).toEulerAngles();
	plane->SetActorRotation(r);*/
}