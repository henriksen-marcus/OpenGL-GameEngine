#include "MeshWalker.h"
#include "Source/Engine/SpringArmComponent.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/Meshes/LightCube.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include "Source/Engine/TriangleSurface.h"
#include "Source/Game/Scenes/HeightmapScene.h"
#include "Source/Game/Scenes/BarycentricScene.h"
#include "Source/Game/LineActor.h"

MeshWalker::MeshWalker(const QVector3D& location)
: Pawn(location)
{
	mCamera = new CameraComponent(this);
	mComponents.push_back(mCamera);
	mCamera->SetFollowParent(false);
	mCamera->bLookAtParent = true;

	mSpringArm = new SpringArmComponent(this, 7.f, 35.f);
	mComponents.push_back(mSpringArm);
	mSpringArm->SetAttachment(mCamera);
    mSpringArm->SetSpringStiffness(100.f);
	//mSpringArm->bEnableCameraLag = false;

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

	mMesh = new CubeMesh(this, 0.5f, QVector3D(0.f, 1.f, 0.f));
    mMesh->bUseLighting = true;
}

void MeshWalker::BeginPlay()
{
	Pawn::BeginPlay();

	mCamera->SetWorldLocation(mSpringArm->GetSocketLocation());
	mSurface = static_cast<BarycentricScene*>(GetWorld())->GetSurface();
}

void MeshWalker::Tick(float deltaTime)
{
	Pawn::Tick(deltaTime);

	// Follow the surface on the map
    auto h = mSurface->GetHeight(GetActorLocation2D());
    mLocation.setY(h+0.4f);

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
	mCamera->SetAsCurrent();
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
        AddActorWorldOffset(mWorldUp * mMovementSpeed);
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
