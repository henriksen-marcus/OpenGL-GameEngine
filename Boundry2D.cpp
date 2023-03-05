#include "Boundry2D.h"
#include "Actor.h"

Boundry2D::Boundry2D()
    : mLocation(QVector2D()),
      mHalfLength(0.f)
{}

Boundry2D::Boundry2D(const QVector2D& location, float halfLength)
    : mLocation(location), mHalfLength(halfLength)
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
