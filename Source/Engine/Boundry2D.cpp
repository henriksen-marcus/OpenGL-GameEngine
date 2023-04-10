#include "Boundry2D.h"
#include "Actor.h"

Boundry2D::Boundry2D()
    : mLocation(QVector2D()),
      mHalfLength(0.f),
	  mOriginalHalfLength(0.f)
{}

Boundry2D::Boundry2D(const QVector2D& location, float halfLength)
    : mLocation(location), mHalfLength(halfLength), mOriginalHalfLength(halfLength)
{
    UpdateMinMaxPoint();
}

void Boundry2D::UpdateLocation(const QVector3D& location)
{
    mLocation = QVector2D(location.x(), location.z());
    UpdateMinMaxPoint();
}

void Boundry2D::UpdateScale(const QVector3D& scale)
{
    // Since the boundary is only a square, we only need to check the largest scale
	const float max = qMax(qMax(scale.x(), scale.y()), scale.z());
	mHalfLength = mOriginalHalfLength * max;
    UpdateMinMaxPoint();
}

void Boundry2D::UpdateMinMaxPoint()
{
    minPoint = mLocation - QVector2D(mHalfLength, mHalfLength);
    maxPoint = mLocation + QVector2D(mHalfLength, mHalfLength);
}


bool Boundry2D::Contains(const QVector2D& point) const
{
    //                                 Left wall                                  Right wall
    bool xColl = point.x() >= mLocation.x() - mHalfLength && point.x() <= mLocation.x() + mHalfLength;
    bool yColl = point.y() >= mLocation.y() - mHalfLength && point.y() <= mLocation.y() + mHalfLength;

    return xColl && yColl;
}

bool Boundry2D::Contains(Actor* actor) const
{
    QVector3D pos = actor->GetActorLocation();
    QVector2D point = QVector2D(pos.x(), pos.y());
    return Contains(point);
}

bool Boundry2D::Intersects(Boundry2D* boundry) const
{
    //if (!boundry) return false;
    return
        !(
            boundry->maxPoint.x() < minPoint.x() || // Object is to the left
            boundry->minPoint.x() > maxPoint.x() || // Object is to the right
            boundry->maxPoint.y() < minPoint.y() || // Object is under
            boundry->minPoint.y() > maxPoint.y()    // Object is above
        );
}

bool Boundry2D::Intersects(Actor* actor) const
{
    return Intersects(actor->GetCollisionComponent());
}
