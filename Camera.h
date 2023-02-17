#pragma once

#include <QOpenGLFunctions_4_1_Core>

#include "qmatrix4x4.h"
#include "qvectornd.h"
#include "enums.h"


// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.05f;
const float DEFAULT_FOV =  70.f;
const float MAX_FOV     =  100.f;
const float MIN_FOV     =  35.f;

class Camera : public QOpenGLFunctions_4_1_Core
{
public:
    // camera Attributes
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;
    QMatrix4x4 lookAtMatrix = QMatrix4x4();
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Fov;
    bool isStatic = false;

    Camera(QVector3D position = QVector3D(), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
    {
        Front = QVector3D(0.0f, 0.0f, -1.0f);
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;

        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Fov = DEFAULT_FOV;
        
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    QMatrix4x4& GetViewMatrix()
    {
        lookAtMatrix.setToIdentity();
        lookAtMatrix.lookAt(Position, Position + Front, Up);
        return lookAtMatrix;
    }

    float GetFOV()
    {
        return Fov;
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Movement direction, float deltaTime)
    {
        if (isStatic) return;
        
        float velocity = MovementSpeed * deltaTime;

        switch (direction)
        {
        case FORWARD:
            Position += Front * velocity;
            break;
        case BACKWARD:
            Position -= Front * velocity;
            break;
        case LEFT:
            Position -= Right * velocity;
            break;
        case RIGHT:
            Position += Right * velocity;
            break;
        case UP:
            Position += WorldUp * velocity;
            break;
        case DOWN:
            Position -= WorldUp * velocity;
            break;
        case JUMP:
            break;
        }
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            // This is so cringe, why qt, why
            Pitch = qBound(-89.9f, Pitch, 89.9f);
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Fov = qBound(MIN_FOV, Fov - yoffset, MAX_FOV);
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        QVector3D front;
        front.setX(cos(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
        front.setY(sin(qDegreesToRadians(Pitch)));
        front.setZ(sin(qDegreesToRadians(Yaw)) * cos(qDegreesToRadians(Pitch)));
        Front = front;
        Front.normalize();
        // also re-calculate the Right and Up vector
        // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Right = QVector3D::crossProduct(Front, WorldUp);
        Right.normalize();
        Up = QVector3D::crossProduct(Right, Front);
        Up.normalize();
    }
};
