#pragma once

#include "Actor.h"

class Arrow : public Actor
{
public:
    Arrow(const QVector3D& location = QVector3D(), float length = 1.f, const QVector3D& direction = QVector3D(0.f, 0.f, -1.f), const QVector3D& color = QVector3D(1.f, 1.f, 1.f), bool init = true);

    void Init() override;
    void Draw() override;

    /* Sets the poining direction of the arrow, calculates
     * the needed rotation to get the the given direction,
     * unlike SetActorRotation(). */
    void SetDirection(const QVector3D& direction);

protected:
    void InitLines();
};

