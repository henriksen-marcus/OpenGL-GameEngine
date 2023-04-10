#include "TriangleSurface.h"
#include <functional>
#include <fstream>
#include <qimage.h>
#include <string>
#include "qimagereader.h"
#include "mainwindow.h"

//void TriangleSurface::Init()
//{
//    if (mVertices.empty()) return;
//
//    initializeOpenGLFunctions();
//
//    glGenVertexArrays(1, &mVAO);
//    glBindVertexArray(mVAO);
//
//    glGenBuffers(1, &mVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
//
//    // [x,y,z,r,g,b,u,v]
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    // Normals
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(3);
//
//    if (!mIndices.empty())
//    {
//        glGenBuffers(1, &mIBO);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
//    }
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
//    glBindVertexArray(0); // This should be above the unbind beneath
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
//}
//
//void TriangleSurface::Draw()
//{
//	if (mVertices.empty()) return;
//
//    UseShader(mShaderName);
//
//    // Uniforms specific to the shader.
//    Shader* activeShader = GetActiveShader();
//    activeShader->SendUniforms();
//    if (bUseLighting) activeShader->SetBool("useLighting", true);
//
//    glUniformMatrix4fv(activeShader->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());
//
//    glBindVertexArray(mVAO);
//
//    // Decide if we should use IBO or not
//    if (!mIndices.empty())
//    {
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
//        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    }
//    else glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
//
//    glBindVertexArray(0);
//}

TriangleSurface::TriangleSurface(Actor* parent)
	: MeshComponent(parent)
{
}

void TriangleSurface::FromFunction(std::function<float(float, float)> f, float xmin, float xmax, float ymin,
                                   float ymax, unsigned segments)
{
    mVertices.clear();

    // Seperate h values as the user might not give us a perfect square
    float h_x = (xmax - xmin) / static_cast<float>(segments);
    float h_y = (ymax - ymin) / static_cast<float>(segments);
    
    for (auto x{xmin}; x < xmax; x+=h_x)
    {
        for (auto y{ymin}; y < ymax; y+=h_y)
        {
            float z = f(x, y);
            mVertices.push_back(Vertex(x, z, y, x, y, z));

            z = f(x+h_x, y);
            mVertices.push_back(Vertex(x+h_x, z, y, x+h_x, y, z));

            z = f(x, y+h_y);
            mVertices.push_back(Vertex(x, z, y+h_y, x, y+h_y, z));
            mVertices.push_back(Vertex(x, z, y+h_y, x, y+h_y, z)); // Top left

            z = f(x+h_x, y);
            mVertices.push_back(Vertex(x+h_x, z, y, x+h_x, y, z)); // Bottom right

            z = f(x+h_x, y+h_y);
            mVertices.push_back(Vertex(x+h_x, z, y+h_y, x+h_x, y+h_y, z)); // Top right
        }
    }
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
    mIndices.clear(); // Add a new index vector

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
