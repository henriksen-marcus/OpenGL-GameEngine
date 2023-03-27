#include "Plane.h"
#include "Meshes/PlaneMesh.h"
#include "Texture2D.h"

Plane::Plane(const QVector3D& location, float sizeX, float sizeY, const QVector3D& color, GLenum mode)
{
    mesh = new PlaneMesh(this, location, sizeX, sizeY, color, mode);
    mesh->SetTexture(new Texture2D("../OpenGLMainQt/Textures/wall.jpg"));
    Init();
}

void Plane::Init()
{
    mesh->Init();
}

void Plane::Draw()
{
    mesh->Draw();
}

