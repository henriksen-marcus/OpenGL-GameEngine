#pragma once

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "VertexClasses.h"


class VisualObject : public QOpenGLFunctions_4_1_Core
{
public:
    VisualObject()
    {
        mVAO = mIBO = mVBO = 0;
    }

    virtual ~VisualObject()
    {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mIBO);
        glDeleteBuffers(1, &mVBO);
    }

    /**
     * \brief Load vertex data into GPU memory. Do this before drawing.
     */
    virtual void Init() = 0;
    
    /**
     * \brief Draw the object on the screen. Call this each tick.
     */
    virtual void Draw()
    {
        glBindVertexArray(mVAO);

        // Decide if we should use IBO or not
        if (!mIndices.empty())
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
            glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        
        glBindVertexArray(0);
    }

protected:
    // Stores vertices for the object
    std::vector<Vertex> mVertices;

    // Stores vertex indices for the object
    std::vector<GLuint> mIndices;

    // Model matrix for transformations
    QMatrix4x4 mMatrix;

    // Vertex Array Object
    GLuint mVAO;

    // Index buffer object
    GLuint mIBO;

    // Vertex buffer object
    GLuint mVBO;
};
