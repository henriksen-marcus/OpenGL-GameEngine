#include "LineNPC.h"
#include "Cube.h"

#include <cmath>
#include <cassert>
#include <iostream>

LineNPC::LineNPC(std::function<float(float)> f, float xmin, float xmax, unsigned segments)
{
    mNPC = new Cube(QVector3D(), 0.2f, QVector3D(0.f, 0.f, 1.f));
    mCurve = f;
    FromFunction(f, xmin, xmax, segments);
    mPosAlongLine = min_x;
}

float LineNPC::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

void LineNPC::Init()
{
    mNPC->Init();
    VisualFunction2D::Init();
}

void LineNPC::Draw(GLint mModelLocation)
{
    VisualFunction2D::Draw(mModelLocation);
    mNPC->Draw(mModelLocation);
}

void LineNPC::Tick(float deltaTime)
{
    float xval = Lerp(min_x, max_x, mPosAlongLine);

    QVector3D newPos = GetActorLocation();
    newPos.setX(newPos.x() + xval);
    newPos.setY(newPos.y() + mCurve(xval));
    mNPC->SetActorLocation(newPos);

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
