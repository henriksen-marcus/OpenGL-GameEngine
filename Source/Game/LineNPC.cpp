#include "LineNPC.h"
#include "Source/Engine/Meshes/CubeMesh.h"
#include <cassert>
#include <iostream>

LineNPC::LineNPC(std::function<float(float)> f1, std::function<float(float)> f2, float xmin, float xmax, unsigned segments)
{
    mNPC = new CubeMesh(this, 0.2f, QVector3D(0.f, 0.f, 1.f));
    mCurve1 = f1;
    mCurve2 = f2;
    mCurrentCurve = f1;
    FromFunction(f1, xmin, xmax, segments);
    mPosAlongLine = min_x;
    mSegments = segments;
}

float LineNPC::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

void LineNPC::SwitchFunction(int num)
{
    mCurrentCurve = num == 1 ? mCurve1 : mCurve2;
    FromFunction(mCurrentCurve, min_x, max_x, mSegments);
    Init();
}

void LineNPC::Init()
{
    mNPC->Init();
    VisualFunction2D::Init();
}

void LineNPC::Draw()
{
    VisualFunction2D::Draw();
    mNPC->Draw();
}

void LineNPC::Tick(float deltaTime)
{
    float xval = Lerp(min_x, max_x, mPosAlongLine);

    QVector3D newPos = GetActorLocation();
    newPos.setX(newPos.x() + xval);
    newPos.setY(newPos.y() + mCurrentCurve(xval));
    mNPC->SetWorldLocation(newPos);

    if (isGoingBack)
    {
        mPosAlongLine -= mOffset;
        if (mPosAlongLine < 0.f)
        {
            mPosAlongLine = 0.f;
            isGoingBack = false;
        }
    }
    else
    {

        if (mPosAlongLine > 1.f)
        {
            mPosAlongLine = 1.f;
            isGoingBack = true;
        }
        mPosAlongLine += mOffset;
    }
}
