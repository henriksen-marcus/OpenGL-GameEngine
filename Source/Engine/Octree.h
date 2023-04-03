#pragma once

#pragma once

#include <QVector>
#include "Actor.h"

class OctreeNode
{
public:
    OctreeNode(const QVector3D& center, float size);

    void Subdivide();
    bool IsLeaf() const { return mChildren.empty(); }
    void AddPoint(const QVector3D& point);
    void GetPointsInsideSphere(const QVector3D& center, float radius, QList<QVector3D>& outPoints) const;

private:
    QVector3D mCenter;
    float mSize;
    QVector<QVector3D> mPoints;
    QVector<OctreeNode> mChildren;
};


class Octree
{
public:
    Octree(int maxDepth, int maxObjects, QVector3D position, QVector3D size);

    void Insert(Actor* actor);
    void Clear();
    void DetectCollisions();

private:
    static constexpr int MAX_DEPTH = 10;
    static constexpr int MAX_OBJECTS = 100;

    int mMaxDepth;
    int mMaxObjects;
    QVector3D mPosition;
    QVector3D mSize;
    QVector<Actor*> mObjects;
    Octree* mSubNodes[8];

    void Split();
    int GetSubnodeIndex(Actor* actor);
    void InsertIntoSubnode(Actor* actor);
    void RemoveFromSubnode(Actor* actor);
    bool IsLeafNode();
    bool Intersects(AABB* aabb);
};

