#include "PlayerController.h"
#include "Pawn.h"
#include "CameraComponent.h"


void PlayerController::ProcessKeyboard(const std::vector<Movement>& heldKeys)
{
    for (auto key : heldKeys)
      {
          currentPossessed->ProcessKeyboard(key);
      }
}

void PlayerController::ProcessMouse(float xoffset, float yoffset)
{
    currentPossessed->ProcessMouseMovement(xoffset, yoffset);
}

Pawn* PlayerController::GetCurrentPossessed()
{
    return currentPossessed;
}

void PlayerController::SetCurrentPossessed(Pawn* pawn)
{
    currentPossessed = pawn;
}

CameraComponent* PlayerController::GetCurrentCamera()
{
    return currentCamera;
}

void PlayerController::SetCurrentCamera(CameraComponent* camera)
{
    currentCamera = camera;
}
