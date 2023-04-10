#pragma once

#include "qvectornd.h"

class Actor;

/* Defines a square area with a location
 * and size. Used for collision detection
 * in Quadtree.
*/
class Boundry2D
{
public:
    Boundry2D();
    Boundry2D(const QVector2D& location, float halfLength);

    void UpdateLocation(const QVector3D& location);
    void UpdateScale(const QVector3D& scale);
    void UpdateMinMaxPoint();

    /* Check if a specific point is within
     * this  boundry. */
    bool Contains(const QVector2D& point) const;

    bool Contains(Actor* actor) const;

    /* Check if a given boundry overlaps
     * with this boundry. */
    bool Intersects(Boundry2D* boundry) const;

    bool Intersects(Actor* actor) const;

    QVector2D minPoint, maxPoint;
    QVector2D mLocation;

    /* The location variable is in the centre, so
     * we use half measurements to get to the border. */
    float mHalfLength;
    float mOriginalHalfLength;
};
