#pragma once

template <typename T>
struct Vector4
{
    Vector4() : x(0), y(0), z(0), w(1.0)
    {
    }
    Vector4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_)
    {
    }

    T x;
    T y;
    T z;
    T w;
};

using Vector4D = Vector4<double>;
using Vector4F = Vector4<float>;
using Vector4I = Vector4<int>;