#pragma once

#include "Source/Engine/Actor.h"

/**
 * \brief Simple XYZ cross.
 */
class XYZ : public Actor
{
public:
    XYZ();
	virtual ~XYZ();

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
