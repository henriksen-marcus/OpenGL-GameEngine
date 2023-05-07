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

		// Lerp just because I can
		auto ab = Lerp<QVector3D>(a,b,t);
		auto bc = Lerp<QVector3D>(b,c,t);
		auto cd = Lerp<QVector3D>(c,d,t);
		// lerp-de-lerp-lerp
		auto ab_bc = Lerp<QVector3D>(ab,bc,t);
		auto bc_cd = Lerp<QVector3D>(bc,cd,t);

		return Lerp<QVector3D>(ab_bc,bc_cd,t);
	}

	static constexpr QVector3D CubicBezier(const CubicCurve& curve, float t)
	{
		return CubicBezier(curve.a, curve.b, curve.c, curve.d, t);
	}

	/**
	 * \brief Float interpolation. Use this function in Tick().
	 * \param current The current position.
	 * \param target Target position.
	 * \return The interpolated number.
	 */
	static constexpr float FInterpTo(float current, float target, float deltaTime, float interpSpeed)
	{
		if (interpSpeed <= 0.f) return target;

		const float dist = target - current;

		// If distance is small, just set the target location
		if (dist * dist < 1.0e-8f) return target;

		// Delta Move, Clamp so we do not over shoot.
		const float deltaMove = dist * std::clamp(deltaTime * interpSpeed, 0.f, 1.f);

		return current + deltaMove;
	}

	/**
	 * \brief Vector interpolation. Use this function in Tick().
	 * \param current The current position.
	 * \param target Target position.
	 * \return The interpolated position.
	 */
	static constexpr QVector3D VInterpTo(const QVector3D& current, const QVector3D& target, float deltaTime, float interpSpeed)
	{
		if (interpSpeed <= 0.f) return target;

		const QVector3D dist = target - current;

		// If distance is small, just set the target location
		const float epsilon = 0.001f;
		if (dist.lengthSquared() < epsilon * epsilon) return target;

		// Delta move, clamp so we do not over shoot
		const float alpha = std::clamp(deltaTime * interpSpeed, 0.0f, 1.0f);
		const QVector3D deltaMove = dist * alpha;

		return current + deltaMove;
	}

	static QVector3D VInterpConstantTo(const QVector3D& current, const QVector3D& target, float deltaTime, float interpSpeed)
	{
		const QVector3D delta = target - current;
		const float deltaM = delta.length();
		const float maxStep = interpSpeed * deltaTime;

		if (deltaM > maxStep)
		{
			if (maxStep > 0.f)
			{
				const QVector3D deltaN = delta.normalized();
				return current + deltaN * maxStep;
			}
			else
			{
				return current;
			}
		}

		return target;
	}

	static float FInterpConstantTo(float Current, float Target, float DeltaTime, float InterpSpeed)
	{
		const float Dist = Target - Current;

		// If distance is too small, just set the desired location
		if (powf(Dist, 2) < 1.0e-8f)
		{
			return Target;
		}

		const float Step = InterpSpeed * DeltaTime;
		return Current + std::clamp(Dist, -Step, Step);
	}
}


