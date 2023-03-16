#pragma once

#include "Actor.h"


/* Info for the constructor of the
   Axis class. */
struct FAxisInfo
{
    int numAxis{3};
    float lineInterval{0.1f};
    float lineSize{0.1f};

    QVector3D length{1.f,1.f,1.f};

    QVector3D xColor{1.f,0.f,0.f};
    QVector3D yColor{0.f,1.f,0.f};
    QVector3D zColor{0.f,0.f,1.f};
};

class Axis : public Actor
{
public:
    Axis(const FAxisInfo& axisInfo, bool init = false);

    void Draw() override;

protected:
    int mNumAxis;
};
