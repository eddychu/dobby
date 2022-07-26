#pragma once
#include "vector3.h"
Vector3D barycentric(const Vector3D &p, const Vector3D &a, const Vector3D &b, const Vector3D &c)
{
    auto v0 = b - a, v1 = c - a, v2 = p - a;
    double d00 = dot(v0, v0);
    double d01 = dot(v0, v1);
    double d11 = dot(v1, v1);
    double d20 = dot(v2, v0);
    double d21 = dot(v2, v1);
    double denom = d00 * d11 - d01 * d01;
    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;
    return Vector3D(u, v, w);
}