#pragma once

#include "Source/Engine/Actor.h"

class VisualPoints : public Actor
{
public:
    VisualPoints(const QVector3D& position = QVector3D(), GLint pointSize = 1);

    virtual void AddPoints(const std::vector<QPointF>& points, const QVector3D& color = QVector3D(1.f, 1.f, 1.f));

    void Draw() override;

protected:
    GLint mPointSize{1};
};
