#pragma once

#include "../math/Vec3.h"
#include "../math/Mat4.h"

class camera {

    public:

        Vec3 position;

        Vec3 forward;
        Vec3 up;
        Vec3 right;

        camera(Vec3 position, Vec3 forward, Vec3 up);

        Mat4 getViewMatrix() const;

        float rotationY;

};