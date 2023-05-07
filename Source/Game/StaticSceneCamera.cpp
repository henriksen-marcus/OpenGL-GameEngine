#include "StaticSceneCamera.h"
#include "Source/Engine/CameraComponent.h"
#include "Source/Engine/PlayerController.h"

StaticSceneCamera::StaticSceneCamera()
{
    camera1 = new CameraComponent(this);
    camera1->bFollowParentTransform = false;
    camera1->bFollowParentRotation = false;
    camera1->SetWorldLocation(QVector3D(0.f, 2.8f, 2.5f)); // Recessed
    //camera1->AddWorldRotation(QQuaternion::fromEulerAngles(QVector3D()))
    //camera1->mPitch = -43.f;
    camera1->mFOV = 85.f;

    camera2 = new CameraComponent(this);
    camera2->bFollowParentTransform = false;
    camera2->bFollowParentRotation = false;
    //camera2->SetWorldLocation(QVector3D(-0.8f, 0.8f, -2.8f));
    camera2->SetWorldLocation(QVector3D(0.f, 0.5f, -2.f));
    //camera2->mYaw = -270.f;
    //camera2->mPitch = -50.f;
    camera2->mFOV = 125.f;
    //camera2->AddWorldRotation(QQuaternion::fromEulerAngles(QVector3D(-30.f, -140.f, 0.f)));

    activeCamera = camera1;
    mComponents.push_back(camera1);
    mComponents.push_back(camera2);
}

CameraComponent* StaticSceneCamera::GetCurrentCamera()
{
    return activeCamera;
}

CameraComponent* StaticSceneCamera::SwapCamera()
{
    if (activeCamera == camera1)
        activeCamera = camera2;
    else
        activeCamera = camera1;

    PlayerController::GetInstance().SetCurrentCamera(activeCamera);
    return activeCamera;
}

void StaticSceneCamera::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);
}
