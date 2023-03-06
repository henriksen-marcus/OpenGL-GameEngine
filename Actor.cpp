﻿#include "Actor.h"
#include "SceneComponent.h"
#include "iostream"
#include "Cube.h"

// I hate Qt

Actor::Actor(const QVector3D& location, bool init)
{
    mLocation = location;
    if (init) Init();
}

void Actor::Init()
{
    if (mVertices.empty()) return;

    initializeOpenGLFunctions();

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

    if (!mIndices.empty())
    {
        glGenBuffers(1, &mIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void Actor::Draw(GLint mModelLocation)
{
    if (mVertices.empty()) return;

    glBindVertexArray(mVAO);

    // Draw with no transformations we we have not gotten the shader "model" location.
    if (mModelLocation != -1)
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, mMatrix.constData());
    }
    else
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    }

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
    mLocation += mForward * offset.z() + QVector3D::crossProduct(mForward, mUp) * offset.x() + mUp * offset.y();
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
    mRotationQuat = QQuaternion::fromEulerAngles(rotation);
    UpdateModelMatrix();
}

void Actor::AddActorLocalRotation(const QVector3D& offset)
{
    mRotation += offset;
    mRotationQuat += QQuaternion::fromEulerAngles(offset);
    UpdateModelMatrix();
}

void Actor::SetActorRotation(const QQuaternion& rotation)
{
    mRotationQuat = rotation;
    UpdateModelMatrixQuat();
}

void Actor::AddActorLocalRotation(const QQuaternion& offset)
{
    mRotationQuat *= offset;
    UpdateModelMatrixQuat();
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

Boundry2D* Actor::GetCollisionComponent()
{
    return mCollisionComponent;
}

void Actor::SetCollisionComponent(Boundry2D* boundry)
{
    mCollisionComponent = boundry;
}

void Actor::SetCollisionComponent(float halfLength)
{
    mCollisionComponent = new Boundry2D(QVector2D(mLocation.x(), mLocation.y()), halfLength);
}

void Actor::Tick(float deltaTime)
{
    if (mCollisionComponent)
        mCollisionComponent->Update(mLocation);

    for (auto c : mComponents)
        c->Tick(deltaTime);
}

void Actor::UpdateModelMatrix()
{
    UpdateVectors();

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

void Actor::UpdateModelMatrixQuat()
{
    mMatrix.setToIdentity();
    mMatrix.translate(mLocation);
    mMatrix.rotate(mRotationQuat);
    mMatrix.scale(mScale);
}

void Actor::UpdateVectors()
{
    // Prevent gimball lock
    //mRotation.setX(qBound(-90.0f, mRotation.x(), 90.0f));

    mForward = QQuaternion::fromAxisAndAngle(mUp, mRotation.y()).rotatedVector(mForward);
    mForward = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(mForward, mUp), mRotation.x()).rotatedVector(mForward);
    mUp = QQuaternion::fromAxisAndAngle(mForward, mRotation.z()).rotatedVector(mUp);
    mRight = QVector3D::crossProduct(mForward, mUp).normalized();

    return;
    mForward.setX(cos(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    mForward.setY(sin(qDegreesToRadians(mPitch)));
    mForward.setZ(sin(qDegreesToRadians(mYaw)) * cos(qDegreesToRadians(mPitch)));
    mForward.normalize();
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mRight = QVector3D::crossProduct(mForward, mWorldUp);
    mRight.normalize();
    mUp = QVector3D::crossProduct(mRight, mForward);
    mUp.normalize();
}
