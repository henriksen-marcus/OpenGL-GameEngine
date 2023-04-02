#include "LineActor.h"
#include "Meshes/LineMesh.h"
LineActor::LineActor(const QVector3D& color)
{
	mMesh = new LineMesh(static_cast<Actor*>(this), color);
	mMesh->SetFollowParent(true);
}

void LineActor::Update(const QVector3D& start, const QVector3D& end)
{
	SetActorLocation(start);
	QVector3D direction = end - start;
	auto rotation = QQuaternion::rotationTo(mRotationQuat.toEulerAngles(), direction.normalized());
	AddActorLocalRotation(rotation);
	float length = direction.length();
	mMesh->SetWorldScale(QVector3D(length, length, length));
}
