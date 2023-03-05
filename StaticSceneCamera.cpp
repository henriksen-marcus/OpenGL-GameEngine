#include "StaticSceneCamera.h"
#include "CameraComponent.h"
#include "PlayerController.h"

StaticSceneCamera::StaticSceneCamera()
{
    camera1 = new CameraComponent(this);
    camera1->followParentTransform = false;
    camera1->followParentRotation = false;
    camera1->SetWorldLocation(QVector3D(0.f, 1.f, 3.5f)); // Recessed
    //camera1->AddWorldRotation(QQuaternion::fromEulerAngles(QVector3D()))
    camera1->mPitch = -10.f;

    camera2 = new CameraComponent(this);
    camera2->followParentTransform = false;
    camera2->followParentRotation = false;
    camera2->SetWorldLocation(QVector3D());

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
