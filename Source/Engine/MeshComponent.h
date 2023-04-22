#pragma once

#include "SceneComponent.h"
#include "VertexClasses.h"

class Timer;
class Texture2D;

/* Holds mesh data. */
class MeshComponent : public SceneComponent
{
public:
    MeshComponent(Actor* parent, GLenum drawMode = GL_TRIANGLES);
    ~MeshComponent();

    void LoadMesh(const std::string& path);
    void LoadFromOBJ(const std::string& path);

    void SetTexture(Texture2D* texture);
    void SetTexture(const std::string& path);

    /**
     * \brief Generates normals for smooth shading.
     * Per-triangle normal generation.
     */
    void GenerateNormals();

    /**
     * \brief Generates normals for smooth shading.
     * Per-quad normal generation.
     */
    void GenerateQuadNormals();

    void GenerateNeighbors();

    float GetHeight(const QVector2D& point);

    Vertex GetVertex(int index) const { return mVertices[index]; }

    unsigned int GetMeshHeight();
    unsigned int GetMeshWidth();

    virtual void Init();
    virtual void Draw();

    std::string mShaderName;
    bool bUseLighting{false};

    /* The index of the triangle in mIndices we are currently on. */
    int triangleIndex{0};

    Timer* mTimer;

protected:
    Texture2D* mTexture;
    QVector3D mColor{1.f, 1.f, 1.f};
    GLenum mDrawMode;
    bool bSmoothShading{true};

    // Stores vertices for the object
    std::vector<Vertex> mVertices;

    // Stores vertex indices for the object
    std::vector<GLuint> mIndices;

    std::vector<int> mNeighbors;

    // Vertex Array Object
    GLuint mVAO{};

    // Index buffer object
    GLuint mIBO{};

    // Vertex buffer object
    GLuint mVBO{};
};

