#pragma once

#include "VisualObject.h"

class Texture2D;

/* Holds vertex data. */
class MeshComponent : public VisualObject
{
public:
    MeshComponent();

    void SetTexture(Texture2D* texture);

    void Init() override;
    void Draw() override;

protected:
    Texture2D* mTexture;
};

