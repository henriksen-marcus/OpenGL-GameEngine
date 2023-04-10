#pragma once

#include "qvector2d.h"

class Math
{
public:
	template<class T>
	static float Lerp(const T& start, const T& end, const float t)
	{
		return start + t * (end - start);
	}

//	/**
//	 * \brief Calculate the barycentric coordinates of a point in a triangle.
//	 * \param point The point to calculate the barycentric coordinates for.
//	 * \param _p1 P
//	 * \param _p2 Q
//	 * \param _p3 R
//	 * \return u, v, w
//	 */
//	static QVector3D Barycentric(const QVector3D& _point, const QVector3D& _p1, const QVector3D& _p2,
//	                             const QVector3D& _p3)
//	{
//		/*auto p1 = _p1;
//		auto p2 = _p2;
//		auto p3 = _p3;
//		auto point = _point;
//		point.setY(0.f);
//
//		p1.setY(0.f);
//		p2.setY(0.f);
//		p3.setY(0.f);
//
//		auto v12 = p2 - p1;
//		auto v13 = p3 - p1;
//		auto norm = QVector3D::crossProduct(v12, v13);
//		float area = norm.length();
//
//		auto p = p2 - point;
//		auto q = p3 - point;
//		norm = QVector3D::crossProduct(p, q);
//		float u = norm.z() / area;
//
//		p = p3 - point;
//		q = p1 - point;
//		norm = QVector3D::crossProduct(p, q);
//		float v = norm.z() / area;
//
//		p = p1 - point;
//		q = p2 - point;
//		norm = QVector3D::crossProduct(p, q);
//		float w = norm.z() / area;
//
//		return QVector3D(u, v, w);*/
//
//		QVector3D v0 = _p2 - _p1;
//		QVector3D v1 = _p3 - _p1;
//		QVector3D v2 = _point - _p1;
//
//		float d00 = QVector3D::dotProduct(v0, v0);
//		float d01 = QVector3D::dotProduct(v0, v1);
//		float d11 = QVector3D::dotProduct(v1, v1);
//		float d20 = QVector3D::dotProduct(v2, v0);
//		float d21 = QVector3D::dotProduct(v2, v1);
//
//		float denom = d00 * d11 - d01 * d01;
//
//		float v = (d11 * d20 - d01 * d21) / denom;
//		float w = (d00 * d21 - d01 * d20) / denom;
//		float u = 1.0f - v - w;
//
//		//qDebug() << "Barycentric: " << u << " " << v << " " << w;
//		return QVector3D(u, v, w);
//	}
//
//	static QVector3D Barycentric(QVector2D point, QVector2D p1, QVector2D p2, QVector2D p3)
//	{
//		auto p12 = p2-p1;
//		auto p13 = p3-p1;
//		auto n = Cross(p12, p13);
//		float areal_123 = n.length();
//		QVector3D baryc;
//
//		// u
//		auto p = p2 - point;
//		auto q = p3 - point;
//		n = Cross(p, q);
//		baryc.setX(n.z()/areal_123);
//
//		// v
//		p = p3 - point;
//		q = p1 - point;
//		n = Cross(p, q);
//		baryc.setY(n.z()/areal_123);
//
//		// w
//		p = p1 - point;
//		q = p2 - point;
//		n = Cross(p, q);
//		baryc.setZ(n.z()/areal_123);
//
//		// print baryc
//		//qDebug() << "Barycentric: " << baryc;
//
//		return baryc;
//}
//
//	static QVector3D Cross(const QVector2D& v1, const QVector2D& v2)
//	{
//		return QVector3D::crossProduct(QVector3D(v1, 0), QVector3D(v2, 0));
//		//return QVector3D::crossProduct(QVector3D(v1.x(), 0.f, v1.y()), QVector3D(v2.x(), 0.f, v2.y()));
//	}


	static void Barycentric(QVector2D a, QVector2D b, QVector2D c, QVector2D p, float& u, float& v, float& w)
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
};
