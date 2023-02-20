#include "VisualFunction3D.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void VisualFunction3D::Init()
{
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

    modelMatrix = glm::translate(modelMatrix, mLocation);
}

void VisualFunction3D::Draw(GLint modelLocation)
{

    if (modelLocation != -1)
    {
        //printf("x: %f, y: %f, z: %f\n", mLocation.x, mLocation.y, mLocation.z);
        
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    }
    else
    {
        printf("modellocation was -1.");
    }
    
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    glBindVertexArray(0);

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(glm::mat4(1.f)));
}

void VisualFunction3D::FromFunction(std::function<float(float, float)> f, float xmin, float xmax, float ymin,
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

void VisualFunction3D::FromFunction(std::function<float(float, float)> f, glm::vec3 origin, float size,
                                    unsigned segments)
{
    float min = origin.x - size / 2.f;
    float max = origin.x + size / 2.f;

    FromFunction(f, min, max, min, max, segments);
}

void VisualFunction3D::FromFile(std::string fileName)
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
    
    /*
    if (file.is_open()) {
        Vertex v;
        int n;
        file >> n;
        file >> std::ws;
        mVertices.reserve(n);
        
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string val1, val2, val3;
            ss.ignore(1, '(');
            std::getline(std::cin, val1, ',');
            std::getline(std::cin, val2, ',');
            std::getline(std::cin, val3, ')');
            std::cout << val1 << ", " << val2 << ", " << val3 << std::endl;
        }
        
        */
    /*Vertex vertex;
        
        for (int i{}; i < n; i++) {
            in >> vertex;
            mVertices.push_back(vertex);
            std::cout << vertex << std::endl;
        }
        in.close();*/
}


void VisualFunction3D::ToFile(std::string fileName)
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

float VisualFunction3D::Integral(std::function<float(float, float)> f, float xmin, float xmax, float ymin, float ymax,
    unsigned segments)
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
