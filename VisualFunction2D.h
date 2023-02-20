#pragma once

#include <functional>
#include "VisualObject.h"
#include "glm.hpp"
#include "VertexClasses.h"

class VisualFunction2D : public VisualObject
{
public:
    void Init();
    void Draw();

    void FromFunction(std::function<float(float)> f, float xmin, float xmax, unsigned segments);
    void FromFunction(std::function<float(float)> f, glm::vec3 origin, float sizeX, unsigned segments);
    void FromFile(std::string fileName);
    void ToFile(std::string fileName);
};
