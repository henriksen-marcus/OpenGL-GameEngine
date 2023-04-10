#pragma once

#include "Source/Engine/Actor.h"

/**
 * \brief Simple line that bridges between two points.
 */
class LineActor : public Actor
{
public:
	LineActor(const QVector3D& color = QVector3D(1.f, 1.f, 1.f));
	void Update(const QVector3D& start, const QVector3D& end);
};

