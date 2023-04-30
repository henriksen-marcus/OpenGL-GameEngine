#pragma once

#include <functional>
#include "VisualObject.h"
#include "Boundry2D.h"
#include "MeshComponent.h"

class SceneComponent;

class Actor : public VisualObject
{
public:
    /**
     * \param location The starting location of the actor.
     * \param init If we should call init right after construction (saves a line of code).
     */
    Actor(const QVector3D& location = QVector3D(), bool init = false);
    virtual ~Actor();

    void Init() override;

    /**
     * \brief Draw the object on the screen. Call this each tick.
     */
    void Draw() override;

    
    // ---------- Translation ---------- //
    virtual const QVector3D& GetActorLocation() const;
    virtual const QVector2D GetActorLocation2D() const;
    virtual void SetActorLocation(const QVector3D& location);
    virtual void AddActorLocalOffset(const QVector3D& offset);
    virtual void AddActorWorldOffset(const QVector3D& offset);

    // ---------- Rotation ---------- //
    virtual const QVector3D& GetActorRotation();
    virtual void SetActorRotation(const QVector3D& rotation);
    virtual void AddActorLocalRotation(const QVector3D& offset);

    virtual const QQuaternion& GetActorQuatRotation() { return mRotationQuat; }
    virtual void SetActorRotation(const QQuaternion& rotation);
    virtual void AddActorLocalRotation(const QQuaternion& offset);

    virtual QVector3D& GetActorForwardVector() { return mForward; }
    virtual QVector3D& GetActorUpVector() { return mUp; }
    virtual QVector3D GetActorRightVector()
    {
	    return QVector3D::crossProduct(mForward, mUp);
    }

    // ---------- Scale ---------- //
    virtual const QVector3D& GetActorScale();
    virtual void SetActorScale(const QVector3D& rotation);
    virtual void AddActorLocalScale(const QVector3D& offset);
    
    const QMatrix4x4& GetModelMatrix() { return mMatrix; }

    Boundry2D* GetCollisionComponent();
    void SetCollisionComponent(Boundry2D* boundry);
    void SetCollisionComponent(float halfLength);

    virtual void BeginPlay(){};
    virtual void Tick(float deltaTime);
    virtual void OnCollision(){};
    virtual void OnCollision(Actor* otherActor){};
    
    void AddComponent(SceneComponent* component);

    MeshComponent* GetMesh();
    void SetMesh(MeshComponent* mesh);
    void ClearMesh();

    std::string name = "actor";

protected:
    [[deprecated]] void UpdateModelMatrix();
    virtual void UpdateModelMatrixQuat();
    virtual void UpdateVectors();
    virtual void UpdateCollisionScale();

    QVector3D mForward  {0.f, 0.f, -1.f};
    QVector3D mUp       {0.f, 1.f, 0.f};
    QVector3D mWorldUp  {0.f, 1.f, 0.f};

    [[deprecated]] float mPitch{};
    [[deprecated]] float mYaw{};

    Boundry2D* mCollisionComponent;
    MeshComponent* mMesh;
    std::vector<SceneComponent*> mComponents;
};


