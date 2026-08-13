#include "camera.h"
#include "../math/Mat4.h"

#include <cmath>

camera::camera(Vec3 position, Vec3 forward, Vec3 up) :

    position(position),
    forward(forward),
    up(up),
    right(forward.cross(up)),
    yaw (0.0f),
    pitch(0.0f) {}

Mat4 camera::getViewMatrix() const {

    Mat4 result = Mat4::identity();

    result.data[0][0] = right.x;
    result.data[0][1] = right.y;
    result.data[0][2] = right.z;

    result.data[1][0] = up.x;
    result.data[1][1] = up.y;
    result.data[1][2] = up.z;

    result.data[2][0] = -forward.x;
    result.data[2][1] = -forward.y;
    result.data[2][2] = -forward.z;

    result.data[0][3] = -right.dot(position);
    result.data[1][3] = -up.dot(position);
    result.data[2][3] = forward.dot(position);

    return result;

}

void camera::setRotationY(float angle) {

    yaw += angle;

    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    forward.x = -sinYaw;
    forward.y = 0.0f;
    forward.z = -cosYaw;

    right = forward.cross(Vec3(0.0f, 1.0f, 0.0f));

    up = right.cross(forward);

}

void camera::setRotationX(float angle) {

    pitch += angle;

    if (pitch > 1.5f) {
        pitch = 1.5f;
    }

    if (pitch < -1.5f) {
        pitch = -1.5f;
    }

    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);

    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    forward.x = -sinYaw * cosPitch;
    forward.y = sinPitch;
    forward.z = -cosYaw * cosPitch;

    right = forward.cross(Vec3(0.0f, 1.0f, 0.0f));

    up = right.cross(forward);

}

void camera::moveForward(float amount) {

    position = position + forward * amount;

}

void camera::moveRight(float amount) {

    position = position + right * amount;

}

void camera::moveUp(float amount) {

    position = position + up * amount;

}