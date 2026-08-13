#pragma once

#include "../math/Vec3.h"
#include "../math/Mat4.h"

class camera {

    public:

        Vec3 position;

        Vec3 forward;
        Vec3 up;
        Vec3 right;
        
        float yaw;
        float pitch;

        camera(Vec3 position, Vec3 forward, Vec3 up);

        Mat4 getViewMatrix() const;

        void setRotationY(float angle);
        void setRotationX(float angle);
        void moveForward(float amount);
        void moveRight(float amount);
        void moveUp(float amount);

};