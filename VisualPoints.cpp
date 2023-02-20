#include "VisualPoints.h"
#include <iostream>

VisualPoints::VisualPoints(const QVector3D& position, GLint pointSize)
{
    SetActorLocation(position);
    mPointSize = pointSize;
}


void VisualPoints::AddPoints(const std::vector<QPointF>& points, const QVector3D& c)
{
    for (auto p : points)
    {
        mVertices.emplace_back(p.x(), p.y(), 0.f, c.x(), c.y(), c.z(), 0.f, 0.f);
        std::cout << "added point"<<std::endl;
    }
}

void VisualPoints::Draw(GLint mModelLocation)
{
    initializeOpenGLFunctions();

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

    glPointSize(mPointSize);

    glDrawArrays(GL_POINTS, 0, mVertices.size());
    glBindVertexArray(0);
}
