#pragma once

#include "SceneComponent.h"
#include "VertexClasses.h"
#include "qmatrix4x4.h"

class Texture2D;

/* Holds vertex data. */
class MeshComponent : public SceneComponent
{
public:
    MeshComponent(Actor* parent, GLenum drawMode = GL_TRIANGLES);
    ~MeshComponent();

    void SetTexture(Texture2D* texture);
    void SetTexture(std::string path);

    virtual void Init();
    virtual void Draw();

protected:
    Texture2D* mTexture;

    GLenum mDrawMode;

    // Stores vertices for the object
    std::vector<Vertex> mVertices;

    // Stores vertex indices for the object
    std::vector<GLuint> mIndices;

    // Vertex Array Object
    GLuint mVAO{};

    // Index buffer object
    GLuint mIBO{};

    // Vertex buffer object
    GLuint mVBO{};

    //// The world-space location of the object
    //QVector3D mLocation{};

    //// The world-space rotation of the object
    //QVector3D mRotation{};

    //QQuaternion mRotationQuat{};

    //// The world-space scale of the object
    //QVector3D mScale{1.f, 1.f, 1.f};

    //// Handles scaling, rotation and translation of the object
    //QMatrix4x4 mMatrix{};
};

