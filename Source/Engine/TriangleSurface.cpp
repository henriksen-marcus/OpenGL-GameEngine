#include "TriangleSurface.h"
#include <functional>
#include <fstream>
#include <qimage.h>
#include <string>
#include "qimagereader.h"
#include "mainwindow.h"
#include "Source/Utility/Color.h"

TriangleSurface::TriangleSurface(Actor* parent)
	: MeshComponent(parent)
{
}

void TriangleSurface::FromFlat(float xmin, float xmax, float zmin, float zmax, float jump)
{
    int segmentsX = static_cast<int>((xmax - xmin) / jump);
    int segmentsZ = static_cast<int>((zmax - zmin) / jump);

    //std::cout << "Segments: " << segmentsX << "x" << segmentsZ << std::endl;

    for (float x = xmin; x < xmax; x += jump)
    {
	    for (float z = zmin; z < zmax; z += jump)
	    {
		    mVertices.emplace_back(x, 0.f, z, QVector3D(1.f, 1.f, 1.f));
		    mVertices.emplace_back(x+jump, 0.f, z, QVector3D(1.f, 1.f, 1.f));
		    mVertices.emplace_back(x, 0.f, z+jump, QVector3D(1.f, 1.f, 1.f));

            mVertices.emplace_back(x, 0.f, z+jump, QVector3D(1.f, 1.f, 1.f));
		    mVertices.emplace_back(x+jump, 0.f, z, QVector3D(1.f, 1.f, 1.f));
		    mVertices.emplace_back(x+jump, 0.f, z+jump, QVector3D(1.f, 1.f, 1.f));
	    }
    }

    mIndices.clear();
}

void TriangleSurface::FromFlat(float xmin, float xmax, float zmin, float zmax, float distanceX, float distanceZ)
{
    const float x_range = xmax - xmin;
    const float z_range = zmax - zmin;

    if (distanceX > x_range) distanceX = x_range;
    if (distanceZ > z_range) distanceZ = z_range;

    // How far apart each vertex is, how far we will move per iteration
    const float h_x = distanceX;
    const float h_z = distanceZ;

    // Grid resolution on x axis
    const int num_vertices_x = static_cast<int>(std::ceilf((xmax - xmin) / distanceX));
    // Grid resolution on z axis
    const int num_vertices_z = static_cast<int>(std::ceilf((zmax - zmin) / distanceZ));

    std::cout << "h_x: " << h_x << std::endl;
    std::cout << "h_z: " << h_z << std::endl;
    std::cout << "num_vertices_x: " << num_vertices_x << std::endl;
    std::cout << "num_vertices_z: " << num_vertices_z << std::endl;

    float maxx = 0;
    float maxz = 0;

    for (int x = 0; x <= num_vertices_x; x++)
    {
	    for (int z = 0; z <= num_vertices_z; z++)
	    {
            float distX = x * h_x;
            float distZ = z * h_z;

            if (xmin + distX > xmax) distX -= std::abs(distX - xmax);
            if (zmin + distZ > zmax) distZ -= std::abs(distZ - zmax);
            
		    mVertices.emplace_back(xmin + distX, 0.f, zmin + distZ, Color::White);
            //qDebug() << "Vertex: " << xmin + distX << ", 0, " << zmin + distZ;
	    }
    }

    std::cout << "Max X: " << maxx << std::endl;
    std::cout << "Max Z: " << maxz << std::endl;

    for (int x = 0; x < num_vertices_x; x++)
    {
	    for (int z = 0; z < num_vertices_z; z++)
	    {
		    // Calculate the unique vertex index for each corner of the current quad
            int base = x * (num_vertices_z + 1) + z;
            int right = (x + 1) * (num_vertices_z + 1) + z;
            int up = x * (num_vertices_z + 1) + (z + 1);
            int up_right = (x + 1) * (num_vertices_z + 1) + (z + 1);

            //   |\
            //   | \
            //   |__\

            mIndices.push_back(base);
            mIndices.push_back(right);
            mIndices.push_back(up);

            //     __
            //     \  |
            //      \ |
            //       \|
            mIndices.push_back(up);
            mIndices.push_back(right);
            mIndices.push_back(up_right);

            // Debug
            /*std::cout << "x: " << x <<  " z: " << z << std::endl;
            std::cout << "Base: " << base << std::endl;
            std::cout << "Right: " << right << std::endl;
            std::cout << "Up: " << up << std::endl;*/
	    }
    }

    /*std::cout << "Num vertices: " << mVertices.size() << std::endl;
    std::cout << "Num indices: " << mIndices.size() << std::endl;
    std::cout << "Num triangles: " << mIndices.size() / 3 << std::endl;*/
}

void TriangleSurface::FromFunction(std::function<float(float, float)> f, float xmin, float xmax, float zmin, float zmax, unsigned segments)
{
    mVertices.clear();

    // Separate h values as the user might not give us a perfect square
    const float h_x = (xmax - xmin) / static_cast<float>(segments);
    const float h_z = (zmax - zmin) / static_cast<float>(segments);

    int num_vertices_x = segments + 1;
    int num_vertices_y = segments + 1;

    for (int x = 0; x < segments; x++)
    {
	    for (int z = 0; z < segments; z++)
	    {
            float x_val = xmin + x * h_x;
            float z_val = zmin + z * h_z;
            float y_val = f(x_val, z_val);

		    float y = f(x, z);
            mVertices.emplace_back(x_val, y_val, z_val, QVector3D(1.f, 1.f, 1.f));
            mVertices.emplace_back(xmin + (x * h_x), 0.f, zmin + (z * h_z), Color::White);
	    }
    }

    // Indices
    for (int x = 0; x < segments - 1; x++)
    {
	    for (int z = 0; z < segments - 1; z++)
	    {
		    // Calculate the unique vertex index for each corner of the current quad
		    int bottomLeftIndex = x + z * segments;
		    int bottomRightIndex = (x + 1) + z * segments;
		    int topLeftIndex = x + (z + 1) * segments;
		    int topRightIndex = (x + 1) + (z + 1) * segments;

		    // Add the indices for the two triangles of the quad
		    mIndices.push_back(bottomLeftIndex);
		    mIndices.push_back(bottomRightIndex);
		    mIndices.push_back(topLeftIndex);

		    mIndices.push_back(topLeftIndex);
		    mIndices.push_back(bottomRightIndex);
		    mIndices.push_back(topRightIndex);
	    }
    }
    
    //for (auto x{xmin}; x < xmax; x+=h_x)
    //{
    //    for (auto y{zmin}; y < zmax; y+=h_z)
    //    {
    //        float z = f(x, y);
    //        mVertices.push_back(Vertex(x, z, y, x, y, z));

    //        z = f(x+h_x, y);
    //        mVertices.push_back(Vertex(x+h_x, z, y, x+h_x, y, z));

    //        z = f(x, y+h_z);
    //        mVertices.push_back(Vertex(x, z, y+h_z, x, y+h_z, z));
    //        mVertices.push_back(Vertex(x, z, y+h_z, x, y+h_z, z)); // Top left

    //        z = f(x+h_x, y);
    //        mVertices.push_back(Vertex(x+h_x, z, y, x+h_x, y, z)); // Bottom right

    //        z = f(x+h_x, y+h_z);
    //        mVertices.push_back(Vertex(x+h_x, z, y+h_z, x+h_x, y+h_z, z)); // Top right
    //    }
    //}
}

void TriangleSurface::FromFunction(std::function<float(float, float)> f, QVector3D origin, float size, unsigned segments)
{
    float min = origin.x() - size / 2.f;
    float max = origin.x() + size / 2.f;

    FromFunction(f, min, max, min, max, segments);
}

void TriangleSurface::FromTextFile(std::string fileName)
{
    mVertices.clear();
    std::string line;
    std::ifstream file(fileName.c_str());
    if (file.is_open()) {
        int n;
        file >> n;
        mVertices.reserve(n);
        for (int i{}; i < n; ++i) {
            Vertex vertex;
            file >> vertex;
            mVertices.push_back(vertex);
        }
        file.close();
    }
}

void TriangleSurface::ToTextFile(std::string fileName)
{
    std::fstream o;
    o.open(fileName.c_str(), std::ios::out);
    if (o.is_open())
    {
        o << mVertices.size() << std::endl;
        for (int i{}; i < mVertices.size(); i++) {
            o << mVertices[i] << std::endl;
        }
        o.close(); 
    }
}

void TriangleSurface::FromImageFile(const std::string& fileName, float size, float maxHeight, unsigned resolution)
{
    QImageReader::setAllocationLimit(1000000000); // 1GB
    const QImage image(fileName.c_str());
    if (image.isNull()) {
        print("Failed to load image from file: " + fileName);
        return;
    }

    mVertices.clear();
    mIndices.clear();

    float h = size / resolution;
    float hSize = size / 2.f;
    QVector3D color(0.5f, 0.5f, 0.5f);

    const int shortestSide = std::min(image.width(), image.height());
    const float pixelJump = (float)shortestSide / (float)resolution;

    for (int x = 0; x < resolution - 1; x++)
    {
	    for (int y = 0; y < resolution - 1; y++)
	    {
		    // Calculate the unique vertex index for each corner of the current quad
		    int bottomLeftIndex = x + y * resolution;
		    int bottomRightIndex = (x + 1) + y * resolution;
		    int topLeftIndex = x + (y + 1) * resolution;
		    int topRightIndex = (x + 1) + (y + 1) * resolution;

		    // Add the indices for the two triangles of the quad
		    mIndices.push_back(bottomLeftIndex);
		    mIndices.push_back(bottomRightIndex);
		    mIndices.push_back(topLeftIndex);

		    mIndices.push_back(topLeftIndex);
		    mIndices.push_back(bottomRightIndex);
		    mIndices.push_back(topRightIndex);
	    }
    }

    float xp = 0.f;
    float yp = 0.f;
    for (int x = 0; x < resolution; x++)
    {
	    for (int y = 0; y < resolution; y++)
	    {
            float height = image.pixelColor(xp, yp).value() / 255.f * maxHeight;
            mVertices.emplace_back(x * h - hSize, height, y * h - hSize, color, x/(float)resolution, y/(float)resolution);
            yp += pixelJump;
	    }
        xp += pixelJump;
        yp = 0.f;
    }
}

float TriangleSurface::Integral(std::function<float(float, float)> f, float xmin, float xmax, float ymin, float ymax, unsigned segments)
{
    // Seperate h values as the user might not give us a perfect square
    float h_x = (xmax - xmin) / static_cast<float>(segments);
    float h_y = (ymax - ymin) / static_cast<float>(segments);
    
    float volume{};
    
    for (float x = xmin + h_x * 0.5f; x < xmax; x += h_x)
    {
        for (float y = ymin + h_y * 0.5f; y < ymax-x; y += h_y)
        {
            // Here we are calculating the height in the middle
            // of the square.
            volume += h_x * h_y * f(x, y);
        }  
    }
    return volume;
}
