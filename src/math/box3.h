#pragma once
#include "math/vector3.h"
#include <limits>
template <typename T>
class Box3 {
    Vector3<T> min;
    Vector3<T> max;
    Box3()
        :min(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()),
         max(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity())
    {
    }
    Box3(Vector3<T> min_, Vector3<T> max_) : min(min_), max(max_){
    }

};


using Box3D = Box3<double>;
using Box3F = Box3<float>;
