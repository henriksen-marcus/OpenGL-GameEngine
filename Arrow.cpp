#include "Arrow.h"

Arrow::Arrow(const QVector3D& location, float length, const QVector3D& direction, const QVector3D& color, bool init)
{
    SetActorLocation(location);
    SetDirection(direction);

    mVertices.clear();

    float headLength = length / 3.5f; // Length along shaft
    float halfLength = length * 0.5f;

    float headZ = length / 2.f - headLength;

    float headSize = length * 0.2f; // Arrow width
    float halfHeadSize = headSize * 0.5f;

    // Shaft
    mVertices.emplace_back(0.f, 0.f, -halfLength, color.x(), color.y(), color.z(), 0.f, 0.f); // Base
    mVertices.emplace_back(0.f, 0.f, halfLength, color.x(), color.y(), color.z(), 0.f, 0.f); // Cross point

    // Head, square
    mVertices.emplace_back(halfHeadSize, halfHeadSize, headZ, color.x(), color.y(), color.z(), 0.f, 0.f); // 2
    mVertices.emplace_back(-halfHeadSize, halfHeadSize, headZ, color.x(), color.y(), color.z(), 0.f, 0.f); // 3
    mVertices.emplace_back(-halfHeadSize, -halfHeadSize, headZ, color.x(), color.y(), color.z(), 0.f, 0.f); // 4
    mVertices.emplace_back(halfHeadSize, -halfHeadSize, headZ, color.x(), color.y(), color.z(), 0.f, 0.f); // 5

    if (init) Init();
}

void Arrow::InitLines()
{
    mIndices.clear();

   // Shaft
   mIndices.push_back(0); // Base
   mIndices.push_back(1); // Cross point

   // Head - connect points to cross point
   mIndices.push_back(1);
   mIndices.push_back(2);

   mIndices.push_back(1);
   mIndices.push_back(3);

   mIndices.push_back(1);
   mIndices.push_back(4);

   mIndices.push_back(1);
   mIndices.push_back(5);

   // Head - make square
   mIndices.push_back(2);
   mIndices.push_back(3);

   mIndices.push_back(3);
   mIndices.push_back(4);

   mIndices.push_back(4);
   mIndices.push_back(5);

   mIndices.push_back(5);
   mIndices.push_back(2);

}

void Arrow::Init()
{
    InitLines();

    if (mIndices.empty())
    {
        printf("Empty mVertices!");
        return;
    }

    //Actor::Init();

    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    // [x,y,z,r,g,b,u,v]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind
    glBindVertexArray(0); // This should be above the unbind beneath
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind
}

void Arrow::Draw()
{
    initializeOpenGLFunctions();


    glBindVertexArray(mVAO);

    glUniformMatrix4fv(GetActiveShader()->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    // Decide if we should use IBO or not
    if (!mIndices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
}

void Arrow::SetDirection(const QVector3D& direction)
{
    QQuaternion additionalRot = QQuaternion::rotationTo(GetActorForwardVector(), direction);
    AddActorLocalRotation(additionalRot);
}
