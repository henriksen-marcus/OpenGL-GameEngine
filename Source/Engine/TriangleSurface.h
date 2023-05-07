#pragma once

#include "Source/Engine/MeshComponent.h"

class TriangleSurface : public MeshComponent
{
public:
    TriangleSurface(Actor* parent);
    virtual ~TriangleSurface();

    /**
     * \brief Create a flat surface with the given parameters.
     * \param jump Distance between each vertex.
     */
    void FromFlat(float xmin, float xmax, float zmin, float zmax, float jump);

    /**
     * \brief Create a flat surface with the given parameters.
     * \param distanceX Distance between each vertex on the x axis.
     * \param distanceZ Distance between each vertex on the z axis.
     */
    void FromFlat(float xmin, float xmax, float zmin, float zmax, float distanceX, float distanceZ);

    /**
     * \brief Load data points into this object's mVertices array using the given function.
     * \param f The function to draw. Must take two floats and return one float.
     * \param segments How many segments to subdivide the area into, aka resolution.
     */
    void FromFunction(std::function<float(float, float)> f, float xmin, float xmax, float zmin, float zmax, unsigned segments);

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
     * This will not work if the file uses indices for the vertices.
     * \param fileName Path to the file including file name and extension.
     */
    void FromTextFileVertices(std::string fileName);

    /**
     * \brief Load data points into this object's mVertices array using a text file.
     * Indices need to be present in the file for this to work.
     * \param fileName Path to the file including file name and extension.
     */
    void FromTextFileIndices(std::string fileName);

    /**
     * \brief Load data points into a text file from this object's mVertices array.
     * This does not load indices.
     * \param fileName Path to the file including file name and extension.
     * \remarks This object needs to be made in vertices only mode.
     */
    void ToTextFileVertices(std::string fileName);

    /**
     * \brief Load data points into a text file from this object's mVertices array.
     * This does load indices.
     * \param fileName Path to the file including file name and extension.
     * \remarks This object needs to be made using indices.
     */
    void ToTextFileIndices(std::string fileName);

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
