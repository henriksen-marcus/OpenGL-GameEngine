#pragma once
#include "MeshComponent.h"

struct QCurveSegment;

class Bezier : public MeshComponent
{
public:
	Bezier(const QVector3D& start);
	virtual ~Bezier();

	void Init() override = 0;
	/**
	 * \brief Override this function and put your logic
	 * above, then call this base function.
	 */
	virtual void InitPoints();
	void Draw() override;


	/**
	 * \brief Get the point on the composite curve at time t.
	 */
	virtual QVector3D operator()(float t) const = 0;
	
	/**
	 * \brief How many points to use to approximate each
	 * individual curve in the composite curve, when drawing.
	 * Three is the minimum if you want to see any curve.
	 */
	unsigned mResolution;

	QVector3D mColor{1.f, 1.f, 1.f};

	/**
	 * \brief If position and control points should be drawn.
	 * Start and end points are white, control points are red.
	 * Remember to call InitPoints() before drawing.
	 */
	bool bDrawPoints = false;

protected:
	QVector3D mStart;

	std::vector<Vertex> mVertices_points;
	GLuint mVAO_points{};
	GLuint mVBO_points{};
};

