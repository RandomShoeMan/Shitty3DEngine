#pragma once

#include "Vec3.h"

class Mat4 {

    public:

        float data[4][4];

        static Mat4 identity();

        Vec3 operator*(const Vec3& vector) const;

        static Mat4 translation(const Vec3& position);

        Mat4 operator*(const Mat4& other) const;

        static Mat4 rotationY(float angle);

        static Mat4 rotationX(float angle);

        static Mat4 rotationZ(float angle);

        static Mat4 scale(const Vec3& scale);

};

