#pragma once

#include "qvectornd.h"
#include <fstream>

struct Vertex0
{
	float x, y, z, r, g, b;

	Vertex0(float x_, float y_, float z_, float r_=0.f, float g_=0.f, float b_=0.f)
	{
		x = x_;
		y = y_;
		z = z_;

		r = r_;
		g = g_;
		b = b_;
	}

	Vertex0()
	{
		x = y = z = r = g = b = 0.f;
	}
};

struct Indices0
{
	int a, b, c;
    Indices0() { a = b = c = 0; }
};

struct Vertex
{
	float x, y, z, r, g, b, u, v;

	Vertex(float x_, float y_, float z_, float r_=0.f, float g_=0.f, float b_=0.f, float u_=0.f, float v_=0.f)
	{
		x = x_;   r = r_;
		y = y_;   g = g_;
		z = z_;   b = b_;
		
		u = u_;
		v = v_;
	}

    Vertex(const QVector3D& loc, float r_=0.f, float g_=0.f, float b_=0.f, float u_=0.f, float v_=0.f)
    {
        x = loc.x();   r = r_;
        y = loc.y();   g = g_;
        z = loc.z();   b = b_;

        u = u_;
        v = v_;
    }

	Vertex()
	{
		x = y = z = r = g = b = u = v = 0.f;
	}

	// FORMAT: X,Y,Z,R,G,B,U,V
	//! Overloaded ostream operator which writes all vertex data on an open textfile stream
	friend std::ostream& operator << (std::ostream& os, const Vertex& v)
	{
		os << std::fixed;
		os << v.x << "," << v.y << "," << v.z << ",";
		os << v.r << "," << v.g << "," << v.b << ",";
		os << v.u << "," << v.v;
		return os;
	}

	//! Overloaded ostream operator which reads all vertex data from an open textfile stream
	friend std::istream& operator >> (std::istream& is, Vertex& v)
	{
		char t;
		is >> v.x >> t >> v.y >> t >> v.z >> t;
		is >> t >> v.r >> t >> v.g >> t >> v.b >> t;
		is >> t >> v.u >> t >> v.v;
		return is;
	}
};
