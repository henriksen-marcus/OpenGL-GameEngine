#pragma once

#include <vector>

#include "VertexClasses.h"
#include "Actor.h"

/**
 * \brief Simple XYZ cross.
 */
class XYZ : public Actor
{
public:
    XYZ();

	/**
	 * \brief Load the vertex data into memory and save information
	 * about how the shader should interpret that data.
	 */
    void Init() override;

	/**
	 * \brief Render call.
	 */
    void Draw();

private:
    std::vector<Vertex0> mVertices;
};
