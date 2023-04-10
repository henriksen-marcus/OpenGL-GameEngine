#include "PlayerController.h"
#include "Pawn.h"
#include "CameraComponent.h"


void PlayerController::ProcessKeyboard(const std::vector<Movement>& heldKeys)
{
    if (!currentPossessed) return;
    for (auto key : heldKeys)
      {
          currentPossessed->ProcessKeyboard(key);
      }
}

void PlayerController::ProcessMouse(float xoffset, float yoffset)
{
    if (!currentPossessed) return;
    currentPossessed->ProcessMouseMovement(xoffset, yoffset);
}

void PlayerController::ProcessMouseScroll(float yoffset)
{
	if (!currentPossessed) return;
	currentPossessed->ProcessMouseScroll(yoffset);
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
