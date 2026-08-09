#include "Vec3.h"
#include <cmath>

using namespace std;

Vec3::Vec3(float x, float y, float z) {

    this->x = x;
    this->y = y;
    this->z = z;

}

Vec3 Vec3::operator+(const Vec3& other) const {

    return Vec3(

        x + other.x,
        y + other.y,
        z + other.z

    );

}

Vec3 Vec3::operator-(const Vec3& other) const {

    return Vec3(

        x - other.x,
        y - other.y,
        z - other.z

    );

}

Vec3 Vec3::operator*(float value) const {

    return Vec3(

        x * value,
        y * value,
        z * value
    
    );

}

float Vec3::length() const {

    return sqrt(x * x + y * y + z * z);

}

Vec3 Vec3::normalised() const {

    float len = length();

    return Vec3(

        x / len,
        y / len,
        z / len

    );

}

float Vec3::dot(const Vec3& other) const {

    return x * other.x
        + y * other.y
        + z * other.z;

}

Vec3 Vec3::cross(const Vec3& other) const {

    return Vec3(

        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x

    );

}