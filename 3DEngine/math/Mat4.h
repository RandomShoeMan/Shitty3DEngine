#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include <cmath>

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

        static Mat4 perspective (float fov, float aspect, float nearPlane, float farPlane) {

            float tanHalfFov = tan(fov / 2.0f);

            Mat4 result = Mat4::identity();

            result.data[0][0] = 1.0f / (aspect * tanHalfFov);

            result.data[1][1] = 1.0f / tanHalfFov;

            result.data[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

            result.data[2][3] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

            result.data[3][2] = -1.0f;

            result.data[3][3] = 0.0f;

            return result;

        }

        Vec4 operator*(const Vec4& vector) const;

};

