#pragma once

#include <functional>
#include "Source/Engine/Actor.h"

class VisualFunction2D : public Actor
{
public:
    void Init() override;
    void Draw() override;

    void FromFunction(std::function<float(float)> f, float xmin, float xmax, unsigned segments);
    void FromFunction(std::function<float(float)> f, QVector3D origin, float sizeX, unsigned segments);
    void FromFile(std::string fileName);
    void ToFile(std::string fileName);

protected:
    float min_x, max_x;
};
