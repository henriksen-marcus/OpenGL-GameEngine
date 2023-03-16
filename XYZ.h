#pragma once

#include "Actor.h"

/**
 * \brief Simple XYZ cross.
 */
class XYZ : public Actor
{
public:
    XYZ(bool init = false);

	/**
	 * \brief Load the vertex data into memory and save information
	 * about how the shader should interpret that data.
	 */
    void Init() override;

	/**
	 * \brief Render call.
	 */
    void Draw() override;
};
