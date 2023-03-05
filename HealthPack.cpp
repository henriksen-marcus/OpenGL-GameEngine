#include "HealthPack.h"
#include "Pawn.h"
#include "WorldManager.h"
#include <type_traits>


HealthPack::HealthPack(const QVector3D& location) : Actor(location)
{
    float size = 0.2f;
    QVector3D color(1.f,1.f,1.f);

    mVertices.emplace_back(-size, -size, -size, color.x(), color.y(), color.z()); // Origin 0
    mVertices.emplace_back(size, -size, -size, color.x(), color.y(), color.z()); // X 1
    mVertices.emplace_back(-size, size, -size, color.x(), color.y(), color.z()); // Y 2
    mVertices.emplace_back(-size, -size, size, color.x(), color.y(), color.z()); // Z 3

    mVertices.emplace_back(size, -size, size, color.x(), color.y(), color.z()); // XZ 4
    mVertices.emplace_back(size, size, -size, color.x(), color.y(), color.z()); // XY 5

    mVertices.emplace_back(-size, size, size, color.x(), color.y(), color.z()); // ZY 6
    mVertices.emplace_back(size, size, size, color.x(), color.y(), color.z()); // XYZ 7

    // Origin side
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(2);

    mIndices.push_back(1);
    mIndices.push_back(2);
    mIndices.push_back(5);

    mIndices.push_back(0);
    mIndices.push_back(3);
    mIndices.push_back(2);

    mIndices.push_back(2);
    mIndices.push_back(3);
    mIndices.push_back(6);
    // Bottom
    mIndices.push_back(0);
    mIndices.push_back(1);
    mIndices.push_back(3);

    mIndices.push_back(1);
    mIndices.push_back(3);
    mIndices.push_back(4);

    // Opposite origin
    mIndices.push_back(2);
    mIndices.push_back(5);
    mIndices.push_back(6);

    mIndices.push_back(5);
    mIndices.push_back(6);
    mIndices.push_back(7);

    mIndices.push_back(3);
    mIndices.push_back(4);
    mIndices.push_back(6);

    mIndices.push_back(4);
    mIndices.push_back(6);
    mIndices.push_back(7);

    mIndices.push_back(1);
    mIndices.push_back(4);
    mIndices.push_back(5);

    mIndices.push_back(4);
    mIndices.push_back(5);
    mIndices.push_back(7);

    Init();
}

void HealthPack::OnCollision(Actor* otherActor)
{
    // dissapear and have an effect on the other actor
    if (std::is_base_of<Pawn, decltype(*otherActor)>())
    {
        Pawn* otherPawn = dynamic_cast<Pawn*>(otherActor);
        if (otherPawn) otherPawn->OnPickup(type);

        WorldManager::GetInstance().GetWorld()->RemoveActor(this);
    }
}
