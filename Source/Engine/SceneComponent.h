#pragma once

#include <QMatrix4x4>

#include "BaseObject.h"
#include "qquaternion.h"
#include "qvectornd.h"


class Actor;

class SceneComponent : public BaseObject
{
public:
    SceneComponent(Actor* parent);

    /* Attach this object to the given actor. */
    virtual void SetupAttachment(Actor* parent);

    /* Remove the attachment to the current actor
       if there is one. */
    void DetachFromActor();

    void SetFollowParent(bool follow);

    // ---------- Translation ---------- //
    virtual const QVector3D& GetRelativeLocation() { return mRelativeLocation; }
    virtual void SetRelativeLocation(const QVector3D& location);
    virtual void AddRelativeLocation(const QVector3D& offset);

    virtual const QVector3D& GetWorldLocation() { return mWorldLocation; }
    virtual void SetWorldLocation(const QVector3D& location);
    virtual void AddWorldOffset(const QVector3D& offset);

    // ---------- Rotation ---------- //
//    virtual const QVector3D& GetRelativeRotation();
//    virtual void SetRelativeRotation(const QVector3D& rotation);
//    virtual void AddRelativeRotation(const QVector3D& offset);

    virtual const QQuaternion& GetRelativeRotation() { return mRelativeRotation; }
    virtual void SetRelativeRotation(const QQuaternion& rotation);
    virtual void AddRelativeRotation(const QQuaternion& offset);

    virtual const QQuaternion& GetWorldRotation() { return mWorldRotation; }
    virtual void SetWorldRotation(const QQuaternion& rotation);
    virtual void AddWorldRotation(const QQuaternion& offset);
    virtual void AddWorldRotation(const QVector3D& offset);

    virtual QVector3D GetForwardVector() { return mForward; }
    virtual QVector3D GetUpVector() { return mUp; }
    virtual QVector3D GetRightVector() { return QVector3D::crossProduct(mForward, mUp); }

    // ---------- Scale ---------- //
    virtual const QVector3D& GetActorScale() { return mScale; }
    virtual void SetWorldScale(const QVector3D& scale);
    virtual void AddWorldScale(const QVector3D& offset);

    virtual void Tick(float deltaTime);

    virtual void UpdateModelMatrixQuat();
    [[deprecated]] virtual void UpdateModelMatrix();
    virtual void UpdateVectors();

    /* If the component should copy the position
     * of it's owning actor, with an offset. */
    bool bFollowParentTransform{true};
    bool bFollowParentRotation{true};
    bool bFollowParentScale{true};

    QMatrix4x4 mMatrix{};
protected:
    Actor* mParent;

    QVector3D mRelativeLocation{};
    QVector3D mWorldLocation{};

    QQuaternion mRelativeRotation{};
    QQuaternion mWorldRotation{};


    // The world-space scale of the object
    QVector3D mScale{1.f, 1.f, 1.f};

    QVector3D mForward  {0.f, 0.f, -1.f};
    QVector3D mUp       {0.f, 1.f, 0.f};
    QVector3D mWorldUp  {0.f, 1.f, 0.f};
};

