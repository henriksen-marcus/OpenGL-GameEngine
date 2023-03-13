#pragma once

#include "qvectornd.h"
#include "Vendor/eigen/Eigen/eigen"

#include <iostream>

using namespace Eigen;

struct pt { float x{}, y{}, z{}; };

QVector3D task_4_4_4(const std::vector<QPointF>& points)
{
    // A * x = b
    // x = A^(-1) * b

    Matrix<float, 7, 3> aMat;
    aMat.fill(1.f);

    for (int i{}; i < points.size(); i++)
    {
        aMat.row(i) << pow(points[i].x(), 2), points[i].x(), 1;
    }

    // The y vector
    Matrix<float, 7, 1> yVec;

    for (int i{}; i < points.size(); i++)
    {
        yVec(i, 0) = points[i].y();
    }

    Matrix<float, 3, 3> bMat = aMat.transpose() * aMat;

    Matrix<float, 3, 1> cMat = aMat.transpose() * yVec;

    // B * x = c
    // x = B^(-1) * c

    Matrix<float, 3, 1> xVec = bMat.inverse() * cMat;

    std::cout << "result: " << xVec(0,0) << " ," << xVec(1,0) << " ," << xVec(2,0) << std::endl;

    return QVector3D(xVec(0,0), xVec(1,0), xVec(2,0));
}


QVector4D task_4_6_10(const std::vector<QPointF>& points)
{
    // A * x = b
    // x = A^(-1) * b

    Matrix<float, 4, 4> aMat;
    aMat.fill(1.f);

    for (int i{}; i < points.size(); i++)
    {
        aMat.row(i) << pow(points[i].x(), 3), pow(points[i].x(), 2), points[i].x(), 1;
    }

    Matrix<float, 4, 1> bVec;

    for (int i{}; i < points.size(); i++)
    {
        bVec(i, 0) = points[i].y();
    }

    Matrix<float, 4, 1> xVec = aMat.inverse() * bVec;

    std::cout << "result: " << xVec(0,0) << " ," << xVec(1,0) << " ," << xVec(2,0) << ", " << xVec(3,0) << std::endl;

    return QVector4D(xVec(0,0), xVec(1,0), xVec(2,0), xVec(3,0));
}
