#pragma once

#include <functional>

#include "Actor.h"

class VisualFunction3D : public Actor
{
public:
    /**
     * \brief Load the data from the mVertices array into the GPU's memory. Do this before calling Draw().
     */
    void Init() override;
 
    void Draw(GLint mModelLocation = -1) override;

    /**
     * \brief Load data points into this object's mVertices array using the given function.
     * \param f The function to draw. Must take two floats and return one float.
     * \param xmin Minimum x value.
     * \param xmax Maximum x value.
     * \param ymin Minimum y value.
     * \param ymax Maximum y value.
     * \param segments How many segments to subdivide the area into, aka resolution.
     */
    void FromFunction(std::function<float(float, float)> f, float xmin, float xmax, float ymin, float ymax, unsigned segments);

    /**
     * \brief Load data points into this object's mVertices array using the given function.
     * \param f The function to draw. Must take two floats and return one float.
     * \param origin Where the center of the draw area should be.
     * \param size How long a side of the draw square should be.
     * \param segments How many segments to subdivide the area into, aka resolution.
     */
    void FromFunction(std::function<float(float, float)> f, QVector3D origin, float size, unsigned segments);

    /**
     * \brief Load data points into this object's mVertices array using a text file.
     * \param fileName Path to the file including file name and extension.
     */
    void FromFile(std::string fileName);

    /**
     * \brief Load data points into a text file from this object's mVertices array.
     * \param fileName Path to the file including file name and extension.
     */
    void ToFile(std::string fileName);

    float Integral(std::function<float(float, float)> f, float xmin, float xmax, float ymin, float ymax, unsigned segments);
};
