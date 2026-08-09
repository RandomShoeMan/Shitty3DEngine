#pragma once

#include <string>

class shader {

    public:

        shader(const char* vertexPath, const char* fragmentPath);

        void use();

        unsigned int getID() const;

    private:

        unsigned int ID;

        unsigned int compileShader(

            unsigned int type,
            const char* source

        );

};