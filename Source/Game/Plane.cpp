#include "Plane.h"
#include "Source/Engine/Meshes/PlaneMesh.h"
#include "Source/Engine/Texture2D.h"

Plane::Plane(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
{
    mMesh = new PlaneMesh(this, sizeX, sizeY, color, mode);
    mMesh->SetTexture2D(new Texture2D("Assets/Textures/ct.jpg"));
    mMesh->SetFollowParent(true);
    mMesh->mShaderName = "god";
    Init();
}

void Plane::Init()
{
    mMesh->Init();
}

void Plane::Draw()
{
    mMesh->Draw();
}

