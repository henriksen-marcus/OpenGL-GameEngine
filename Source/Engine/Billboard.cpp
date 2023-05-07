#include "Billboard.h"

#include "CameraComponent.h"
#include "Texture2D.h"
#include "PlayerController.h"

Billboard::Billboard(Actor* parent, float sizeX, float sizeY, const QVector3D& color)
	: MeshComponent(parent, GL_TRIANGLES)
{
    // Square
	mVertices.emplace_back(sizeX, 0.f, sizeY, color, 1.f, 0.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(sizeX, 0.f, -sizeY, color, 1.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, -sizeY, color, 0.f, 1.f, 0.f, 1.f, 0.f);
    mVertices.emplace_back(-sizeX, 0.f, sizeY, color, 0.f, 0.f, 0.f, 1.f, 0.f);

    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(0);

    Init();
}

Billboard::~Billboard()
{
}

void Billboard::Tick(float deltaTime)
{
    bFollowParentRotation = false;
    auto camPos = PlayerController::GetInstance().GetCurrentCamera()->GetWorldLocation();
    auto dirFromCam = (mWorldLocation - camPos).normalized();
	auto rot = QQuaternion::rotationTo(QVector3D(0,-1,0), dirFromCam);
	SetWorldRotation(rot);

	MeshComponent::Tick(deltaTime);
}
