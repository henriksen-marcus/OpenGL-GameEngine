#include "VisualFunction2D.h"

#include <fstream>
#include <string>

void VisualFunction2D::Init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    // [x,y,z,r,g,b,u,v]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VisualFunction2D::Draw(GLint mModelLocation)
{
    glBindVertexArray(mVAO);

    // Draw with no transformations we we have not gotten the shader "model" location.
    if (mModelLocation != -1)
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, mMatrix.constData());
    }
    else
    {
        QMatrix4x4 temp;
        glUniformMatrix4fv(1, 1, GL_FALSE, temp.constData());
    }

    glDrawArrays(GL_LINES, 0, mVertices.size());
    glBindVertexArray(0);
}

void VisualFunction2D::FromFunction(std::function<float(float)> f, float xmin, float xmax, unsigned segments)
{
    mVertices.clear();
    min_x = xmin;
    max_x = xmax;

    float h = (xmax - xmin) / static_cast<float>(segments);

    for (auto x{xmin}; x < xmax; x+=h)
    {
        float y = f(x);
        float yh = f(x+h);
        
        mVertices.push_back(Vertex(x, y, 0.f, y > 0 ? y : 0.f, 0.f, y < 0 ? abs(y) : 0.f));
        mVertices.push_back(Vertex(x+h, yh, 0.f, yh > 0 ? yh : 0.f, 0.f, yh < 0 ? abs(yh) : 0.f));
        //printf("i: %d\n", i);
    }
}

void VisualFunction2D::FromFunction(std::function<float(float)> f, QVector3D origin, float sizeX, unsigned segments)
{
    float xmin = min_x = origin.x() - sizeX / 2.f;
    float xmax = max_x = origin.x() + sizeX / 2.f;

    FromFunction(f, xmin, xmax, segments);
}

void VisualFunction2D::FromFile(std::string fileName)
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

void VisualFunction2D::ToFile(std::string fileName)
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
