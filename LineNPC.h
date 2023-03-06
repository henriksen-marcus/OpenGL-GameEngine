#pragma once

#include "VisualFunction2D.h"

class Cube;

class LineNPC : public VisualFunction2D
{
public:
    LineNPC(std::function<float(float)> f, float xmin, float xmax, unsigned segments);
    float Lerp(float a, float b, float t);
    void Init() override;
    void Draw(GLint mModelLocation = -1) override;
    void Tick(float deltaTime) override;

    float mOffset{0.012f};

protected:
    /* The NPC that will move along the line. */
    Cube* mNPC;
    float mPosAlongLine{0.f};
    bool isGoingBack{false};
    std::function<float(float)> mCurve;
};
