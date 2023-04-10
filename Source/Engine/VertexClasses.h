#pragma once

#include "qvectornd.h"
#include <fstream>

struct Vertex
{
	float x, y, z, r, g, b, u, v, a, m, c;

    Vertex(float x_, float y_, float z_, float r_=0.f, float g_=0.f, float b_=0.f, float u_=0.f, float v_=0.f, float a_=0.f, float m_=0.f, float c_=0.f)
	{
		x = x_;   r = r_;	 a = a_;	 
		y = y_;   g = g_;	 m = m_;
		z = z_;   b = b_;	 c = c_;
		
		u = u_;
		v = v_;
	}

    Vertex(const QVector3D& loc, float r_=0.f, float g_=0.f, float b_=0.f, float u_=0.f, float v_=0.f, float a_=0.f, float m_=0.f, float c_=0.f)
    {
        x = loc.x();   r = r_;	a = a_;
        y = loc.y();   g = g_;  m = m_;
        z = loc.z();   b = b_;  c = c_;

        u = u_;
        v = v_;
    }

    Vertex(float x_, float y_, float z_, const QVector3D& col = QVector3D(), float u_=0.f, float v_=0.f, float a_=0.f, float m_=0.f, float c_=0.f)
    {
        x = x_;   r = col.x();   a = a_;
        y = y_;   g = col.y();   m = m_;
        z = z_;   b = col.z();   c = c_;

        u = u_;
        v = v_;
    }

    Vertex(const QVector3D& loc, const QVector3D& col, float u_=0.f, float v_=0.f, float a_=0.f, float m_=0.f, float c_=0.f)
    {
        x = loc.x();   r = col.x();   a = a_;
        y = loc.y();   g = col.y();   m = m_;
        z = loc.z();   b = col.z();   c = c_;

        u = u_;
        v = v_;
    }

	Vertex()
	{
		x = y = z = r = g = b = u = v = a = m = c = 0.f;
	}

	QVector3D GetPos()
    {
	    return QVector3D(x, y, z);
    }

	QVector2D GetPos2D()
    {
	    return QVector2D(x, z);
    }

	QVector3D GetCol()
    {
    	return QVector3D(r, g, b);
	}

	QVector2D GetUV()
    {
    	return QVector2D(u, v);
	}

	QVector3D GetNormal()
    {
    	return QVector3D(a, m, c);
	}

	void SetNormal(const QVector3D& n)
    {
    	a = n.x();
		m = n.y();
		c = n.z();
	}

	void AddNormal(const QVector3D& n)
    {
    	a += n.x();
		m += n.y();
		c += n.z();
	}

	// FORMAT: X,Y,Z,R,G,B,U,V,A,M,C
	//! Overloaded ostream operator which writes all vertex data on an open textfile stream
	friend std::ostream& operator << (std::ostream& os, const Vertex& v)
	{
		os << std::fixed;
		os << v.x << "," << v.y << "," << v.z << ",";
		os << v.r << "," << v.g << "," << v.b << ",";
		os << v.u << "," << v.v << "," << v.a << "," << v.m << "," << v.c;
		return os;
	}

	//! Overloaded ostream operator which reads all vertex data from an open textfile stream
	friend std::istream& operator >> (std::istream& is, Vertex& v)
	{
		char t;
		is >> v.x >> t >> v.y >> t >> v.z >> t;
		is >> t >> v.r >> t >> v.g >> t >> v.b >> t;
		is >> t >> v.u >> t >> v.v >> t >> v.a >> t >> v.m >> t >> v.c;
		return is;
	}
};
