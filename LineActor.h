#pragma once
#include "Actor.h"
class LineActor : public Actor
{
public:
	LineActor(const QVector3D& color = QVector3D(1.f, 1.f, 1.f));
	void Update(const QVector3D& start, const QVector3D& end);
};

