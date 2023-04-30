#pragma once

#include "QVector3D"
#include "Source/Engine/BaseObject.h"

class OBJMaterial : public BaseObject
{
public:
	OBJMaterial() :
	mShininess(0),
	mTransparency(0),
	mOpticalDensity(0),
	mIlluminationModel(0)
	{
	}

	OBJMaterial(
		const std::string& name,
		const QVector3D& ambient,
		const QVector3D& diffuse,
		const QVector3D& specular,
		const QVector3D& emission,
		float shininess,
		float transparency,
		float opticalDensity,
		int illuminationModel
	) :
		mName(name),
		mAmbient(ambient),
		mDiffuse(diffuse),
		mSpecular(specular),
		mEmission(emission),
		mShininess(shininess),
		mTransparency(transparency),
		mOpticalDensity(opticalDensity),
		mIlluminationModel(illuminationModel)
	{}
	virtual ~OBJMaterial(){};

	std::string mName;

	// Ka
	QVector3D mAmbient;

	// Kd
	QVector3D mDiffuse;

	// Ks 
	QVector3D mSpecular;

	// Ke
	QVector3D mEmission;

	// Ns - Specular exponent, weight for specular
	float mShininess;

	// d
	float mTransparency;

	// Ni
	float mOpticalDensity;

	// illum
	int mIlluminationModel;

	// https://en.wikipedia.org/wiki/Wavefront_.obj_file
};