#include "CubePlayer.h"
#include "Cube.h"

CubePlayer::CubePlayer()
{
    mPosessedActor = new Cube(QVector3D(), 0.2f, QVector3D(0.5f, 1.f, 0.2f));
    mPosessedActor->Init();
}

