#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "VertexClasses.h"

#include "BaseObject.h"

class VisualObject : public BaseObject
{
public:
    virtual ~VisualObject()
    {
        if (mVAO) glDeleteVertexArrays(1, &mVAO);
        if (mIBO) glDeleteBuffers(1, &mIBO);
        if (mVBO) glDeleteBuffers(1, &mVBO);
    }

    /**
     * \brief Load vertex data into GPU memory. Do this before drawing.
     */
    virtual void Init() = 0;
    
    /**
     * \brief Draw the object on the screen. Call this each tick.
     */
    virtual void Draw(GLint mModelLocation = -1) = 0;

protected:
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

    // The world-space location of the object
    QVector3D mLocation{};

    // The world-space rotation of the object
    QVector3D mRotation{};

    QQuaternion mRotationQuat{};

    // The world-space scale of the object
    QVector3D mScale{1.f, 1.f, 1.f};

    // Handles scaling, rotation and translation of the object
    QMatrix4x4 mMatrix{};
};
