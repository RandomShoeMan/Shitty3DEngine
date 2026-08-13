#include "Vec4.h"

Vec4::Vec4(float x, float y, float z, float w) :
    x(x),
    y(y),
    z(z),
    w(w) {}

Vec4 Vec4::perspectiveDivide() const {

    return Vec4(

        x / w,
        y / w,
        z / w,
        1.0f

    );
}