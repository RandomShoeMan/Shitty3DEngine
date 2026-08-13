#pragma once

#include <vector>
#include "../math/Vec3.h"

class OBJLoader {

public:

    std::vector<Vec3> vertices;
    std::vector<unsigned int> indices;

    bool load(const char* filename);

};