#include "Actor.h"

// I hate Qt

void Actor::Init()
{
    if (mVertices.empty()) return;

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    
    // [x,y,z,r,g,b,u,v]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void Actor::Draw(GLint mModelLocation)
{
    glBindVertexArray(mVAO);

    // Draw with no transformations we we have not gotten the shader "model" location.
    if (mModelLocation != -1)
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    } else
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    }


    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    
    glBindVertexArray(0);
}


// ---------- Translation ---------- //

const QVector3D& Actor::GetActorLocation()
{
    return mLocation;
}

void Actor::SetActorLocation(const QVector3D& location)
{
    mLocation = location;
    UpdateModelMatrix();
}

void Actor::AddActorLocalOffset(const QVector3D& offset)
{
    mLocation += offset;
    UpdateModelMatrix();
}



// ---------- Rotation ---------- //

const QVector3D& Actor::GetActorRotation()
{
    return mRotation;
}

void Actor::SetActorRotation(const QVector3D& rotation)
{
    mRotation = rotation;
    UpdateModelMatrix();
}

void Actor::AddActorLocalRotation(const QVector3D& offset)
{
    mRotation += offset;
    UpdateModelMatrix();
}



// ---------- Scaling ---------- //

const QVector3D& Actor::GetActorScale()
{
    return mScale;
}

void Actor::SetActorScale(const QVector3D& scale)
{
    mScale = scale;
    UpdateModelMatrix();
}

void Actor::AddActorLocalScale(const QVector3D& offset)
{
    mScale += offset;
    UpdateModelMatrix();
}

void Actor::UpdateModelMatrix()
{
    mMatrix = QMatrix4x4();
    mMatrix.setToIdentity();
    mMatrix.translate(mLocation);

    // Pitch
    mMatrix.rotate(mRotation.x(), QVector3D(1.f, 0.f, 0.f));
    // Yaw
    mMatrix.rotate(mRotation.y(), QVector3D(0.f, 1.f, 0.f));
    // Roll
    mMatrix.rotate(mRotation.z(), QVector3D(0.f, 0.f, 1.f));

    mMatrix.scale(mScale);
}
