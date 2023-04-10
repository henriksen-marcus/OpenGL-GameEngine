#pragma once

#include "VisualFunction2D.h"

class CubeMesh;

class LineNPC : public VisualFunction2D
{
public:
    LineNPC(std::function<float(float)> f1, std::function<float(float)> f2, float xmin, float xmax, unsigned segments);
    void SwitchFunction(int num);
    void Init() override;
    void Draw() override;
    void Tick(float deltaTime) override;

    float mOffset{0.012f};

protected:
    /* The NPC that will move along the line. */
    CubeMesh* mNPC;
    float mPosAlongLine{0.f};
    bool isGoingBack{false};
    std::function<float(float)> mCurrentCurve;
    std::function<float(float)> mCurve1;
    std::function<float(float)> mCurve2;
    int mSegments;
};
