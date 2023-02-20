#pragma once

#include "qquaternion.h"
#include "qvectornd.h"
#include <QOpenGLFunctions_4_1_Core>

class VisualObject;
class Actor;

class SceneComponent : public QOpenGLFunctions_4_1_Core
{
public:
    SceneComponent();

    /* Attch this object to the given actor. */
    void SetupAttachment(Actor* parent);

    /* Remove the attahcment to the current actor
       if there is one. */
    void DetachFromActor();

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

    virtual const QQuaternion& GetWorldRotation() { return mRelativeRotation; }
    virtual void SetWorldRotation(const QQuaternion& rotation);
    virtual void AddWorldRotation(const QQuaternion& offset);

    virtual QVector3D& GetForwardVector() { return mForward; }
    virtual QVector3D& GetUpVector() { return mUp; }
    virtual QVector3D& GetRightVector() { return mRight; }

    // ---------- Scale ---------- //
    virtual const QVector3D& GetActorScale() { return mScale; }
    virtual void SetActorScale(const QVector3D& rotation);
    virtual void AddActorLocalScale(const QVector3D& offset);

protected:
    VisualObject* mParent;

    QVector3D mRelativeLocation{};
    QVector3D mWorldLocation{};

    QQuaternion mRelativeRotation{};
    QQuaternion mWorldRotation{};

    // The world-space scale of the object
    QVector3D mScale{1.f, 1.f, 1.f};

    QVector3D mForward  {0.f, 0.f, 1.f};
    QVector3D mUp       {0.f, 1.f, 0.f};
    QVector3D mWorldUp  {0.f, 1.f, 0.f};
    QVector3D mRight    {1.f, 0.f, 0.f};
};

