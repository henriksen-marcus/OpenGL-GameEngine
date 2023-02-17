#pragma once

#include <functional>
#include "VisualObject.h"

class Actor : public VisualObject
{
public:
    /**
     * \param location The starting location of the actor.
     * \param init If we should call init right after construction (saves a line of code).
     */
    Actor(const QVector3D& location = QVector3D(), bool init = false)
    {
        mLocation = location;
        //if (init) Init();
    }

    void Init() override;

    /**
     * \brief Draw the object on the screen. Call this each tick.
     * \param modelLocation The location in the vertex shader of the model matrix
     */
    virtual void Draw(GLint mModelLocation = -1) override;

    
    // ---------- Translation ---------- //
    virtual const QVector3D& GetActorLocation();
    virtual void SetActorLocation(const QVector3D& location);
    virtual void AddActorLocalOffset(const QVector3D& offset);

    // ---------- Rotation ---------- //
    virtual const QVector3D& GetActorRotation();
    virtual void SetActorRotation(const QVector3D& rotation);
    virtual void AddActorLocalRotation(const QVector3D& offset);

    // ---------- Scale ---------- //
    virtual const QVector3D& GetActorScale();
    virtual void SetActorScale(const QVector3D& rotation);
    virtual void AddActorLocalScale(const QVector3D& offset);
    
    const QMatrix4x4& GetModelMatrix() { return mMatrix; }
    
protected:
    virtual void UpdateModelMatrix();
};


