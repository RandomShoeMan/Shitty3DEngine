#pragma once

#include "../math/Mat4.h"
#include <string>

class shader {

    public:

        shader(const char* vertexPath, const char* fragmentPath);

        void use();

        unsigned int getID() const;

        void setMat4(const char* name, const Mat4& matrix);

    private:

        unsigned int ID;

        unsigned int compileShader(

            unsigned int type,
            const char* source

        );

};