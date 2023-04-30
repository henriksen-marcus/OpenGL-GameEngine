#pragma once

#include "Actor.h"
#include "Bezier.h"

struct QuadraticCurve;

/* Quadratic curve segment */
struct QCurveSegment
{
	QCurveSegment(const QVector3D& control_, const QVector3D& point_)
	: control(control_), point(point_){}

	QVector3D control;
	QVector3D point;
};

/**
 * \brief A composite curve put together by multiple cubic bezier curves.
 */
class QuadraticBezier : public Bezier
{
public:
	QuadraticBezier(const QVector3D& start);
	virtual ~QuadraticBezier();

	void Init() override;
	void InitPoints() override;

	/**
	 * \brief Append a segment to the composite curve.
	 * \param segment The control point for the previous
	 * existing point in the composite curve and the new point.
	 */
	void AddSegment(const QCurveSegment& segment);
	QVector3D operator()(float t) const override;

	/**
	 * \brief Get the curve at index.
	 */
	const QuadraticCurve& operator[](int index) const;

protected:
	std::vector<QuadraticCurve> mCurves;
};

