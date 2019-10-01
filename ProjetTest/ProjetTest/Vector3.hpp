#ifndef IMAGE_SYNTHESIS_VEC3_H
#define IMAGE_SYNTHESIS_VEC3_H

#include <iostream>
#include <cmath>

template<typename T>
struct Vector3 {
    T x, y, z;

    Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3(const T &x, const T &y, const T &z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float dot(const Vector3 &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    float squaredNorm() const {
        return this->dot(*this);
    }

    float norm() const {
        return sqrt(this->squaredNorm());
    }

    bool operator==(const Vector3 &rhs) const {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    bool operator!=(const Vector3 &rhs) const {
        return !(rhs == *this);
    }

    Vector3<T> operator+(const Vector3 &rhs) const {
        return Vector3<T>{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vector3<T> operator-(const Vector3 &rhs) const {
        return Vector3<T>{x - rhs.x, y - rhs.y, z - rhs.z};
    }

    Vector3<T> operator*(const Vector3 &rhs) const {
        return Vector3<T>{x * rhs.x, y * rhs.y, z * rhs.z};
    }

    Vector3<T> operator/(const Vector3 &rhs) const {
        return Vector3<T>{x / rhs.x, y / rhs.y, z / rhs.z};
    }

    friend Vector3<T> operator*(const float &scalar, const Vector3<T> &rhs) {
        return Vector3<T>{scalar * rhs.x, scalar * rhs.y, scalar * rhs.z};
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3<T> &vector3) {
        return os << "[" << vector3.x << ", " << vector3.y << ", " << vector3.z << "]";
    }
};

#endif
