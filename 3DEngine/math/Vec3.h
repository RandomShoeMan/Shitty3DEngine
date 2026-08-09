#pragma once

class Vec3 {

    public:

        float x;
        float y;
        float z;

        Vec3(float x, float y, float z);

        Vec3 operator+(const Vec3& other) const;

        Vec3 operator-(const Vec3& other) const;

        Vec3 operator*(float value) const;

        float length() const;

        Vec3 normalised() const;

        float dot(const Vec3& other) const;

        Vec3 cross(const Vec3& other) const;

};
