#include "Mat4.h"

#include <cmath>

Mat4 Mat4::identity() {

    Mat4 result{};

    result.data[0][0] = 1.0f;
    result.data[1][1] = 1.0f;
    result.data[2][2] = 1.0f;
    result.data[3][3] = 1.0f;

    return result;

}

Vec3 Mat4::operator*(const Vec3& vector) const {

    float x = data[0][0] * vector.x
            + data[0][1] * vector.y
            + data[0][2] * vector.z
            + data[0][3];

    float y = data[1][0] * vector.x
            + data[1][1] * vector.y
            + data[1][2] * vector.z
            + data[1][3];

    float z = data[2][0] * vector.x
            + data[2][1] * vector.y
            + data[2][2] * vector.z
            + data[2][3];

    return Vec3(x, y, z);

}

Mat4 Mat4::translation(const Vec3& position) {

    Mat4 result = Mat4::identity();

    result.data[0][3] = position.x;
    result.data[1][3] = position.y;
    result.data[2][3] = position.z;

    return result;

}

Mat4 Mat4::operator*(const Mat4& other) const {

    Mat4 result{};

    for (int row = 0; row < 4; row++) {

        for (int column = 0; column < 4; column++) {

            for (int i = 0; i < 4; i++) {

                result.data[row][column] += data[row][i] * other.data[i][column];

            }

        }

    }

    return result;

}

Mat4 Mat4::rotationY(float angle) {

    Mat4 result = Mat4::identity();

    float c = std::cos(angle);
    float s = std::sin(angle);

    result.data[0][0] = c;
    result.data[0][2] = s;

    result.data[2][0] = -s;
    result.data[2][2] = c;

    return result;

}

Mat4 Mat4::rotationX(float angle) {

    Mat4 result = Mat4::identity();

    float c = std::cos(angle);
    float s = std::sin(angle);

    result.data[1][1] = c;
    result.data[1][2] = s;

    result.data[2][1] = -s;
    result.data[2][2] = c;

    return result;

}

Mat4 Mat4::rotationZ(float angle) {

    Mat4 result = Mat4::identity();

    float c = std::cos(angle);
    float s = std::sin(angle);

    result.data[0][0] = c;
    result.data[1][0] = s;

    result.data[0][1] = -s;
    result.data[1][1] = c;

    return result;

}

Mat4 Mat4::scale(const Vec3& scale) {

    Mat4 result = Mat4::identity();

    result.data[0][0] = scale.x;
    result.data[1][1] = scale.y;
    result.data[2][2] = scale.z;

    return result;
    
}

Vec4 Mat4::operator*(const Vec4& vector) const {

    return Vec4(

        data[0][0] * vector.x +
        data[0][1] * vector.y +
        data[0][2] * vector.z +
        data[0][3] * vector.w,

        data[1][0] * vector.x +
        data[1][1] * vector.y +
        data[1][2] * vector.z +
        data[1][3] * vector.w,

        data[2][0] * vector.x +
        data[2][1] * vector.y +
        data[2][2] * vector.z +
        data[2][3] * vector.w,

        data[3][0] * vector.x +
        data[3][1] * vector.y +
        data[3][2] * vector.z +
        data[3][3] * vector.w

    );
}