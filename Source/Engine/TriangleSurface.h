#pragma once

#include "Source/Engine/MeshComponent.h"

class TriangleSurface : public MeshComponent
{
public:
    TriangleSurface(Actor* parent);

    /*void Init() override;
    void Draw() override;*/

    /**
     * \brief Load data points into this object's mVertices array using the given function.
     * \param f The function to draw. Must take two floats and return one float.
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
    void FromTextFile(std::string fileName);

    /**
     * \brief Load data points into a text file from this object's mVertices array.
     * \param fileName Path to the file including file name and extension.
     */
    void ToTextFile(std::string fileName);

    /**
     * \brief Creates a surface from a heightmap image file.
     * The object is centered at the origin.
     * \param fileName Path including file name and extension.
     * \param maxHeight The maximum height of the surface.
     * \param size The length of the side of the square.
     */
    void FromImageFile(const std::string& fileName, float size, float maxHeight, unsigned resolution);

    float Integral(std::function<float(float, float)> f, float xmin, float xmax, float ymin, float ymax, unsigned segments);
};
