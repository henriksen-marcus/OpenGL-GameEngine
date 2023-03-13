#pragma once

#include "VisualObject.h"

/* Holds vertex data. */
class MeshComponent : public VisualObject
{
public:
    MeshComponent();

    void Init() override;
    void Draw(GLint mModelLocation = -1) override;
};

