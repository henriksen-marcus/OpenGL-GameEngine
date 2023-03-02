//#include "Octree.h"

//#include "Octree.h"
//#include "AABB.h"

//Octree::Octree(int maxDepth, int maxObjects, QVector3D position, QVector3D size)
//    : mMaxDepth(maxDepth), mMaxObjects(maxObjects), mPosition(position), mSize(size)
//{
//    for (int i = 0; i < 8; i++)
//    {
//        mSubNodes[i] = nullptr;
//    }
//}

//void Octree::Insert(Actor* actor)
//{
//    if (IsLeafNode())
//    {
//        mObjects.push_back(actor);
//        return;
//        Split();
//    }

//    int subnodeIndex = GetSubnodeIndex(actor);
//    mSubNodes[subnodeIndex]->Insert(actor);
//}

//void Octree::Clear()
//{
//    for (int i = 0; i < 8; i++)
//    {
//        if (mSubNodes[i] != nullptr)
//        {
//            mSubNodes[i]->Clear();
//            delete mSubNodes[i];
//            mSubNodes[i] = nullptr;
//        }
//    }

//    mObjects.clear();
//}

//void Octree::DetectCollisions()
//{
//    for (int i = 0; i < mObjects.size(); i++)
//    {
//        for (int j = i + 1; j < mObjects.size(); j++)
//        {
//            if (mObjects[i]->Intersects(mObjects[j]))
//            {
//                mObjects[i]->OnCollision(mObjects[j]);
//                mObjects[j]->OnCollision(mObjects[i]);
//            }
//        }
//    }

//    if (!IsLeafNode())
//    {
//        for (int i = 0; i < 8; i++)
//        {
//            if (mSubNodes[i] != nullptr)
//            {
//                mSubNodes[i]->DetectCollisions();
//            }
//        }
//    }
//}

//void Octree::Split()
//{
//    QVector3D subSize = mSize / 2.0f;

//    mSubNodes[0] = new Octree(mMaxDepth - 1, mMaxObjects, mPosition + QVector3D(0, 0, 0), subSize);
//    mSubNodes[1] = new Octree(mMaxDepth - 1, mMaxObjects, mPosition + QVector3D(subSize.x(), 0, 0), subSize);
//    mSubNodes[2] = new Octree(mMaxDepth - 1, mMaxObjects, mPosition + QVector3D(0, subSize.y(), 0), subSize);
//    mSubNodes[3] = new Octree

