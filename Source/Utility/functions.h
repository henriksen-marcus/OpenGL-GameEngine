#pragma once

#include <cmath>

float myfunc(float x, float y)
{
    return sin(M_PI * x) * sin(M_PI * y);
}

float myfunc2(float x, float y)
{
    return pow(x,2) + pow(y,2);
}

float myfunc3(float x, float y)
{
    return -1.f * abs(sin(x) * cos(y) * exp(abs(1 - (sqrt(pow(x,2)+pow(y,2) / M_PI)))));
}

float oblig1_3func(float x, float y)
{
    return 1 - x - y;
}

float my2dfunc(float x)
{
    return cos(x);
}
