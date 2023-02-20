#pragma once

#include "Actor.h"

class VisualPoints : public Actor
{
public:
    VisualPoints(const QVector3D& position = QVector3D(), GLint pointSize = 1);

    void Init() override { Actor::Init(); };

    virtual void AddPoints(const std::vector<QPointF>& points, const QVector3D& color = QVector3D(1.f, 1.f, 1.f));

    void Draw(GLint mModelLocation = -1) override;

protected:
    GLint mPointSize{1};
};
