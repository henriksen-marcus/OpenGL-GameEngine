#include "Axis.h"

Axis::Axis(const FAxisInfo& a, bool init)
{
    mNumAxis = a.numAxis;

    mVertices.emplace_back(QVector3D(), a.xColor);
    mVertices.emplace_back(QVector3D(1.f, 0.f, 0.f) * a.length.x(), a.xColor);

    mVertices.emplace_back(QVector3D(), a.yColor);
    mVertices.emplace_back(QVector3D(0.f, 1.f, 0.f) * a.length.y(), a.yColor);

    if (mNumAxis > 2)
    {
        mVertices.emplace_back(QVector3D(), a.zColor);
        mVertices.emplace_back(QVector3D(0.f, 0.f, 1.f) * a.length.z(), a.zColor);
    }

    if (a.lineInterval > 0.f)
    {
        float l = a.lineSize * 0.5f;
        for (float i = a.lineInterval; i <= a.length.x(); i+= a.lineInterval)
        {
            mVertices.emplace_back(i, l, 0.f, a.xColor);
            mVertices.emplace_back(i, -l, 0.f, a.xColor);
        }

        for (float i = a.lineInterval; i <= a.length.y(); i+= a.lineInterval)
        {
            mVertices.emplace_back(l, i, 0.f, a.yColor);
            mVertices.emplace_back(-l, i, 0.f, a.yColor);
        }

        for (float i = a.lineInterval; i <= a.length.z(); i+= a.lineInterval)
        {
            mVertices.emplace_back(0.f, l, i, a.zColor);
            mVertices.emplace_back(0.f, -l, i, a.zColor);
        }
    }

    if (init) Init();
}

void Axis::Draw()
{
    initializeOpenGLFunctions();

    glBindVertexArray(mVAO);

    glUniformMatrix4fv(GetActiveShader()->GetModelLocation(), 1, GL_FALSE, mMatrix.constData());

    glDrawArrays(GL_LINES, 0, mVertices.size());
    glBindVertexArray(0);
}

