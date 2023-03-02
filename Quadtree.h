#pragma once

#include <vector>
#include "Actor.h"
#include "Boundry2D.h"

class myStaticClass
{
public:
    void Add(const QVector2D& item) {arr.push_back(item);}
    std::vector<QVector2D> arr;
     static myStaticClass& GetInstance()
     {
         static myStaticClass instance;
         return instance;
     }

private:
     myStaticClass(){}
     ~myStaticClass(){}

     myStaticClass(const myStaticClass&) = delete;
     myStaticClass& operator = (const myStaticClass&) = delete;
};


class Quadtree : public Actor
{
public:
    Quadtree(const Boundry2D& boundry, float _z);

    // 4 sub-sections
    Quadtree* nw;
    Quadtree* ne;
    Quadtree* sw;
    Quadtree* se;

    float z;
    float incr{0.3f};

    // Current collision object in this node
    std::vector<Actor*> mActors;

    Boundry2D mBoundry;

    bool IsLeaf() { return mActors.empty(); }

    // Add an actor to this node (doesn't fit further down)
    void Insert(Actor* actor);

    // Get the deepest node that fits this location
    Quadtree* Find(const QVector2D& location);

    // Divide the node into 4 subnodes
    void Split();

    void Subdivide();

    // Get a list of actors overlapping the specified bounding box
    void Query(std::vector<Actor*>& found, const Boundry2D& boundry);



    void InitLines(std::vector<Vertex>& arr);
    void Init() override;
    void Draw(GLint mModelLocation = -1) override;

protected:
    bool mIsDivided{false};

    static constexpr unsigned MAX_CAPACITY = 4;
};
