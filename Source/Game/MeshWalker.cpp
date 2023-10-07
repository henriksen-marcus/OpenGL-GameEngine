#include "MeshWalker.h"
#include "Source/Engine/SpringArmComponent.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/Meshes/LightCube.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Game/Scenes/HeightmapScene.h"
#include "Source/Game/Scenes/BarycentricScene.h"
#include "Source/Game/Scenes/Eksamen2023Scene.h"
#include "Source/Game/LineActor.h"
#include "Source/Engine/PlayerController.h"
#include "Source/Engine/Timer.h"
#include "Source/Engine/Texture3D.h"


MeshWalker::MeshWalker(const QVector3D& location)
: Pawn(location)
{
	mThirdPersonCamera = new CameraComponent(this);
	mComponents.push_back(mThirdPersonCamera);
	mThirdPersonCamera->SetFollowParent(false);
	mThirdPersonCamera->bLookAtParent = true;

    mFirstPersonCamera = new CameraComponent(this);
    mComponents.push_back(mFirstPersonCamera);
    mFirstPersonCamera->SetFollowParent(true);
    mFirstPersonCamera->bLookAtParent = false;
    mFirstPersonCamera->AddRelativeLocation({ 0.f, 0.2f, -0.8f });

	mSpringArm = new SpringArmComponent(this, 7.f, 35.f);
	mComponents.push_back(mSpringArm);
	mSpringArm->SetAttachment(mThirdPersonCamera);
    mSpringArm->SetSpringStiffness(100.f);
	mSpringArm->bEnableCameraLag = false;

	mLightCube = new LightCube(this, 0.05f);
	mComponents.push_back(mLightCube);
	//mLightCube->SetRelativeLocation(QVector3D(0.f, 3.f, 0.f));
    mLightCube->SetFollowParent(false);

    auto* lightSpring = new SpringArmComponent(this, 2.f, 90.f);
    mComponents.push_back(lightSpring);
    lightSpring->SetAttachment(mLightCube);
    lightSpring->SetSpringStiffness(300.f);
    lightSpring->SetMass(4.f);
    lightSpring->SetDamping(20.f);

    mLine = new LineActor(QVector3D(1.f, 1.f, 0.f));
    GetWorld()->mRenderer->Add("mLine", mLine);

    SetCollisionComponent(0.25f);

	mMesh = new CubeMesh(this, 0.5f, QVector3D(1.f, 1.f, 1.f));
    mMesh->bFollowParentScale = true;
    mMesh->SetTexture2D("Assets/Textures/wall.jpg");
    mMesh->bUseLighting = false;
    mMesh->Init();

    switchTimer = new Timer();
    switchTimer->Start();

    lightTimer = new Timer();
    lightTimer->Start();
}

void MeshWalker::BeginPlay()
{
	Pawn::BeginPlay();

	mThirdPersonCamera->SetWorldLocation(mSpringArm->GetSocketLocation());
	mSurface = GetWorld()->GetSurface();
    mLightCube->SetWorldLocation({0, 2, 0});
}

void MeshWalker::Tick(float deltaTime)
{
	Pawn::Tick(deltaTime);

    if (mSurface)
    {
        // Follow the surface on the map
        auto h = mSurface->GetHeight(GetActorLocation2D());
        mLocation.setY(h + 0.4f);
    }

    mLine->Update(mLocation, mLightCube->GetWorldLocation());
}

void MeshWalker::Draw()
{
	Pawn::Draw();
	mLightCube->Draw();
}

void MeshWalker::SetAsCurrent()
{
	Pawn::SetAsCurrent();
	mThirdPersonCamera->SetAsCurrent();
}

void MeshWalker::ProcessKeyboard(Movement direction)
{
	switch (direction)
    {
    case Movement::FORWARD:
        AddActorWorldOffset(mForward*mMovementSpeed);
        break;
    case Movement::BACKWARD:
        AddActorWorldOffset(-mForward * mMovementSpeed);
        break;
    case Movement::LEFT:
        AddActorWorldOffset(-GetActorRightVector() * mMovementSpeed);
        break;
    case Movement::RIGHT:
        AddActorWorldOffset(GetActorRightVector() * mMovementSpeed);
        break;
    case Movement::UP:
        SwitchCamera();
        break;
    case Movement::DOWN:
        AddActorWorldOffset(-mWorldUp * mMovementSpeed);
        break;
    case Movement::JUMP:
        break;
	case ROTATE_LEFT:
        AddActorLocalRotation(QVector3D(0.f, 1.f, 0.f));
        break;
	case ROTATE_RIGHT:
        AddActorLocalRotation(QVector3D(0.f, -1.f, 0.f));
        break;
    }
}

void MeshWalker::OnPickup(PickupType pickup)
{
    switch (pickup)
    {
	case PickupType::Health:
        static_cast<Eksamen2023Scene*>(GetWorld())->AddScore();
		break;
	case PickupType::Damage:
        GetWorld()->RestartGame();
		break;
    case PickupType::Switch:
        if (lightTimer->GetDuration() < 1000) break;
        lightTimer->Reset();
        mLightCube->activateLight = !mLightCube->activateLight;
        print("toggle light");
        break;
	}
}

void MeshWalker::SwitchCamera()
{
    // Make sure we don't spam the switch
    if (switchTimer->GetDuration() < 500) return;
    switchTimer->Reset();
    

    auto* activeCamera = GetPlayerController().GetCurrentCamera();
    if (activeCamera == mThirdPersonCamera)
    {
        GetPlayerController().SetCurrentCamera(mFirstPersonCamera);
	}
    else
    {
        GetPlayerController().SetCurrentCamera(mThirdPersonCamera);
	}
}

void MeshWalker::OnGameReset()
{
    mLightCube->activateLight = true;
}
