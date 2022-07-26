#pragma once

template <typename T>
struct Vector3
{
    Vector3() : x(0), y (0), z(0) {

    }
    Vector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_)
    {
    }

    T x;
    T y;
    T z;
};

template <typename T>
Vector3<T> operator-(const Vector3<T> &lhs, const Vector3<T> &rhs)
{
    return Vector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename T>
T dot(const Vector3<T> &lhs, const Vector3<T> &rhs)
{
    return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z * rhs.z;
}
using Vector3D = Vector3<double>;
using Vector3F = Vector3<float>;
using Vector3I = Vector3<int>;
