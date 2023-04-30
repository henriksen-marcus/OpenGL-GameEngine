#pragma once
#include "Bezier.h"

struct CubicCurve;

/* Cubic curve segment */
struct CCurveSegment
{
	CCurveSegment(const QVector3D& control1_, const QVector3D& control2_, const QVector3D& point_)
	: control1(control1_), control2(control2_), point(point_){}

	QVector3D control1, control2;
	QVector3D point;
};

class CubicBezier : public Bezier
{
public:
	CubicBezier(const QVector3D& start);
	virtual ~CubicBezier();

	void Init() override;
	void InitPoints() override;

	/**
	 * \brief Append a segment to the composite curve.
	 * \param segment The control point for the previous
	 * existing point in the composite curve and the new point.
	 */
	void AddSegment(const CCurveSegment& segment);

	QVector3D operator()(float t) const override;
	const CubicCurve& operator[](int index) const;

protected:
	std::vector<CubicCurve> mCurves;
};

