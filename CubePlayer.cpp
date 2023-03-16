#include "CubePlayer.h"
#include "Cube.h"

CubePlayer::CubePlayer()
{
    mPossessedActor = new Cube(QVector3D(), 0.2f, QVector3D(0.5f, 1.f, 0.2f));
    mPossessedActor->Init();
    mMovementSpeed *= 3.f;
    SetCollisionComponent(0.1f);
}

void CubePlayer::Tick(float deltaTime)
{
    Pawn::Tick(deltaTime);
}

void printQVector3D(const QVector3D& vec) {
    qDebug() << "X:" << vec.x() << "Y:" << vec.y() << "Z:" << vec.z();
}

