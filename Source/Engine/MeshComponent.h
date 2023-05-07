#pragma once

#include "SceneComponent.h"
#include "VertexClasses.h"

class Texture2D;
class Texture3D;
class Timer;
class Texture;
class OBJMaterial;

/* Holds mesh data. */
class MeshComponent : public SceneComponent
{
public:
    MeshComponent(Actor* parent, GLenum drawMode = GL_TRIANGLES);
    ~MeshComponent();

    void LoadMesh(const std::string& path);
    void LoadFromOBJ(const std::string& path);
    std::vector<OBJMaterial*> ParseMTL(const std::string& path);

    /**
     * \brief Sends the mesh data to the GPU again.
     */
    void UpdateMesh();

    void SetTexture2D(Texture2D* texture);
    void SetTexture2D(const std::string& path);

    void SetTexture3D(Texture3D* texture);

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

    /**
     * \brief Not working right now.
     */
    void GenerateNeighbors();

    float GetHeight(const QVector2D& point);

    /**
     * \return The actual vertex at the given index.
     */
    Vertex& GetVertex(int index) { return mVertices[index]; }


	// Not working
    unsigned int GetMeshHeight();
    // Not working
    unsigned int GetMeshWidth();

    /**
     * \brief Releases vertex and index data from CPU memory.
     * \remarks This will stop the mesh from being drawn.
     */
    void ClearMemory();

    virtual void Init();
    virtual void Draw();

    std::string mShaderName;
    bool bUseLighting{false};

    /* The index of the triangle in mIndices we are currently on. */
    int triangleIndex{0};

    Timer* mTimer;

    
protected:
    Texture* mTexture;

    /**
     * \brief What kind of texture we have.
     * No texture: 0,
     * 2D Texture: 2,
     * 3D Texture: 3
     */
    int mTextureDimension{0};
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

