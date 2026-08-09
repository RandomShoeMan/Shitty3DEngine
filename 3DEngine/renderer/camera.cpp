#include "camera.h"
#include "../math/Mat4.h"

camera::camera(Vec3 position, Vec3 forward, Vec3 up) :

    position(position),
    forward(forward),
    up(up),
    right(forward.cross(up)), 
    rotationY(0.0f) {}

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
