#include "Quadtree.h"
#include <iostream>

Quadtree::Quadtree(Boundry2D* boundry, float _z)
    : mBoundry(boundry), z(_z), mIsDivided(false)
{
}

Quadtree::~Quadtree()
{
    if (mIsDivided) {
        if (nw != nullptr) delete nw;
        if (ne != nullptr) delete ne;
        if (sw != nullptr) delete sw;
        if (se != nullptr) delete se;
    }
    delete mBoundry;

    /* We don't delete the actors because the
     * the quadtree doesn't own them. */
}

void Quadtree::Insert(Actor* actor)
{
    if (!actor) return;

    /* If this node doesn't contain the center
     * position of the new actor, let another node
     * handle it. */
    if (!mBoundry->Contains(actor)) return;

    /* If we get too many objects in this node,
     * split it into four to allow for more
     * efficient collision detection. */
    if (mActors.size() < MAX_CAPACITY) mActors.push_back(actor);
    else
    {
        Subdivide();

        /* Try to assign the actor to all our children.
         * Remember because of recursion, if the actor's
         * position doesn't fit inside the child's position
         * it will just return. So this is fine. */
        this->nw->Insert(actor);
        this->ne->Insert(actor);
        this->sw->Insert(actor);
        this->ne->Insert(actor);
    }
}

void Quadtree::Remove(Actor* actor)
{
    // If this node doesn't contain the actor, check children
    if (!mBoundry->Contains(actor))
    {
        if (mIsDivided)
        {
            nw->Remove(actor);
            ne->Remove(actor);
            sw->Remove(actor);
            se->Remove(actor);

            // If all children are empty, delete them
            CheckChildren();
        }
        return;
    }

    // Remove the actor from this node
    auto it = std::find(mActors.begin(), mActors.end(), actor);
    if (it != mActors.end()) mActors.erase(it);

    // If all children are empty, delete them
    CheckChildren();
}

void Quadtree::RemoveAllActors()
{
    mActors.clear();

    if (mIsDivided)
    {
        ne->RemoveAllActors();
        nw->RemoveAllActors();
        se->RemoveAllActors();
        sw->RemoveAllActors();
        CheckChildren();
    }
}

void Quadtree::UpdateTree(const std::vector<Actor*>& existingActors)
{
    RemoveAllActors();

    for (auto actor : existingActors)
        if (actor->GetCollisionComponent())
            Insert(actor);
}

void Quadtree::CheckChildren()
{
    if (!mIsDivided) return;
   //if (nw && nw->IsLeaf() && ne && ne->IsLeaf() && sw && sw->IsLeaf() && se && se->IsLeaf())
    //{
        /*if (nw != nullptr) delete nw;
        if (ne != nullptr) delete ne;
        if (sw != nullptr) delete sw;
        if (se != nullptr) delete se;*/

        nw = ne = sw = se = nullptr;
        mIsDivided = false;
    //}
}

void Quadtree::Subdivide()
{
    if (mIsDivided) return;
    mIsDivided = true;

    float newHL = mBoundry->mHalfLength * 0.5f;
    QVector2D loc = mBoundry->mLocation;

    this->nw = new Quadtree(new Boundry2D(QVector2D(loc.x()-newHL, loc.y()+newHL), newHL), z+incr);
    this->ne = new Quadtree(new Boundry2D(QVector2D(loc.x()+newHL, loc.y()+newHL), newHL), z+incr);
    this->sw = new Quadtree(new Boundry2D(QVector2D(loc.x()-newHL, loc.y()-newHL), newHL), z+incr);
    this->se = new Quadtree(new Boundry2D(QVector2D(loc.x()+newHL, loc.y()-newHL), newHL), z+incr);

}

void Quadtree::Query(std::vector<Actor*>& found, Boundry2D* boundry)
{
    // If this node's boundry is completely outside the given boundry
    if (!mBoundry->Intersects(boundry)) return;

    // Check for actors inside self
    for (auto actor : mActors)
    {
        // Here we check for the actual collision
        if (boundry->Intersects(actor)) found.push_back(actor);
    }

    if (mIsDivided)
    {
        // Gather the overlapped items from the children recursively
        nw->Query(found, boundry);
        ne->Query(found, boundry);
        sw->Query(found, boundry);
        se->Query(found, boundry);
    }
}

void Quadtree::InitLines(std::vector<Vertex>& arr)
{
    z = 0;
    QVector2D loc = mBoundry->mLocation;
    float hl = mBoundry->mHalfLength;

    // Square
    arr.emplace_back(loc.x() - hl, loc.y() + hl, z, 1.f);
    arr.emplace_back(loc.x() + hl, loc.y() + hl, z, 1.f);

    arr.emplace_back(loc.x() + hl, loc.y() + hl, z, 1.f);
    arr.emplace_back(loc.x() + hl, loc.y() - hl, z, 1.f);

    arr.emplace_back(loc.x() + hl, loc.y() - hl, z, 1.f);
    arr.emplace_back(loc.x() - hl, loc.y() - hl, z, 1.f);

    arr.emplace_back(loc.x() - hl, loc.y() - hl, z, 1.f);
    arr.emplace_back(loc.x() - hl, loc.y() + hl, z, 1.f);

    if (mIsDivided)
    {
        nw->InitLines(arr);
        ne->InitLines(arr);
        sw->InitLines(arr);
        se->InitLines(arr);
    }
}

void Quadtree::Init()
{
    InitLines(mVertices);
    for (auto i : mVertices)
    {
        i.z = i.y;
        i.y = 0.5f;
    }
    Actor::Init();
}

void Quadtree::Draw()
{
    glBindVertexArray(mVAO);

    QMatrix4x4 temp{};
    glUniformMatrix4fv(GetActiveShader()->GetModelLocation(), 1, GL_FALSE, temp.constData());

    glDrawArrays(GL_LINES, 0, mVertices.size());

    glBindVertexArray(0);
}


