#pragma once

template <typename T>
struct Vector2
{
    Vector2() : x(0), y(0) {

    }
    Vector2(T x_, T y_) : x(x_), y(y_)
    {
    }

    T x;
    T y;
};

template <typename T>
Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
T dot(const Vector2<T> &lhs, const Vector2<T> &rhs)
{
    return lhs.x * rhs.x + lhs.y + rhs.y;
}

using Vector2D = Vector2<double>;
using Vector2F = Vector2<float>;
using Vector2I = Vector2<int>;
