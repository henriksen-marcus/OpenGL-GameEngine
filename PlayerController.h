#pragma once

#include "BaseObject.h"
#include "enums.h"

class Pawn;
class CameraComponent;

class PlayerController : public BaseObject
{
public:
    static PlayerController& GetInstance()
    {
        static PlayerController instance;
        return instance;
    }

    void ProcessKeyboard(const std::vector<Movement>& heldKeys);
    void ProcessMouse(float xoffset, float yoffset);

    Pawn* GetCurrentPossessed();
    void SetCurrentPossessed(Pawn* pawn);

    CameraComponent* GetCurrentCamera();
    void SetCurrentCamera(CameraComponent* camera);

private:
    PlayerController(){}
    ~PlayerController(){}

    PlayerController(const PlayerController&) = delete;
    PlayerController& operator = (const PlayerController&) = delete;

    Pawn* currentPossessed;

    // Need to be updated by the actor holding the camera
    CameraComponent* currentCamera;
};
