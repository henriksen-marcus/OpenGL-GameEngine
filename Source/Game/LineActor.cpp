#include "LineActor.h"
#include "Source/Engine/Meshes/LineMesh.h"

LineActor::LineActor(const QVector3D& color)
{
	mMesh = new LineMesh(static_cast<Actor*>(this), color);
	mMesh->SetFollowParent(true);
}

void LineActor::Update(const QVector3D& start, const QVector3D& end)
{
	// Calculate the distance between the start and end points
    QVector3D diff = end - start;
    float length = diff.length();

    // Calculate the rotation quaternion needed to rotate the line to point in the correct direction
    QQuaternion rotation = QQuaternion::rotationTo(QVector3D(0, 0, 1), diff.normalized());

    // Set the actor's location, rotation, and scale to match the start and end points
    SetActorLocation(start);
    SetActorRotation(rotation);
    SetActorScale(QVector3D(1, 1, length));
}
