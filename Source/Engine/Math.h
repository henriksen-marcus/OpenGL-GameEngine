#pragma once

#include "qvector2d.h"

struct QuadraticCurve
{
	// Starting point
	QVector3D a;
	// Control point
	QVector3D b;
	// End point
	QVector3D c;
};

struct CubicCurve
{
	// Starting point
	QVector3D a;
	// Control point
	QVector3D b, c;
	// End point
	QVector3D d;
};

namespace Math
{
	template<class T>
	static constexpr T Lerp(const T& start, const T& end, const float t)
	{
		return start + t * (end - start);
	}

	static constexpr void Barycentric(QVector2D a, QVector2D b, QVector2D c, QVector2D p, float& u, float& v, float& w)
	{
		QVector2D v0 = b - a, v1 = c - a, v2 = p - a;
		float d00 = QVector2D::dotProduct(v0, v0);
		float d01 = QVector2D::dotProduct(v0, v1);
		float d11 = QVector2D::dotProduct(v1, v1);
		float d20 = QVector2D::dotProduct(v2, v0);
		float d21 = QVector2D::dotProduct(v2, v1);
		float denom = d00 * d11 - d01 * d01;
		v = (d11 * d20 - d01 * d21) / denom;
		w = (d00 * d21 - d01 * d20) / denom;
		u = 1.0f - v - w;
	}

	/**
	 * \param a Starting point.
	 * \param b Control point.
	 * \param c End point.
	 * \param t Time.
	 * \return The point on the quadratic bezier curve at time t.
	 */
	static constexpr QVector3D QuadraticBezier(const QVector3D& a, const QVector3D& b, const QVector3D& c, float t)
	{
		const float u = 1.0f - t;
	    const float tt = t * t;
	    const float uu = u * u;
	    const QVector3D p = uu * a + 2.0f * u * t * b + tt * c;
	    return p;
	}

	static constexpr QVector3D QuadraticBezier(const QuadraticCurve& curve, float t)
	{
		return QuadraticBezier(curve.a, curve.b, curve.c, t);
	}

	static constexpr QVector3D CubicBezier(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D& d, float t)
	{
		/*const float u = 1.0f - t;
		const float tt = t * t;
		const float uu = u * u;
		const QVector3D p = uu * u * a + 3.0f * uu * t * b + 3.0f * u * tt * c + tt * t * d;*/

		auto ab = Lerp<QVector3D>(a,b,t);
		auto bc = Lerp<QVector3D>(b,c,t);
		auto cd = Lerp<QVector3D>(c,d,t);

		auto ab_bc = Lerp<QVector3D>(ab,bc,t);
		auto bc_cd = Lerp<QVector3D>(bc,cd,t);

		return Lerp<QVector3D>(ab_bc,bc_cd,t);
	}

	static constexpr QVector3D CubicBezier(const CubicCurve& curve, float t)
	{
		return CubicBezier(curve.a, curve.b, curve.c, curve.d, t);
	}
};


