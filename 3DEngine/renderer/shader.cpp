#include "shader.h"

#include <glad/gl.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

shader::shader(const char* vertexPath, const char* fragmentPath) {

    string vertexCode;
    string fragmentCode;
    
    ifstream vertexFile(vertexPath);
    ifstream fragmentFile(fragmentPath);

    if (!vertexFile.is_open()) {

        cout << "Failed to open vertex shader!" << endl;

    }

    cout << "Opened vertex shader..." << endl;

    if (!fragmentFile.is_open()) {

        cout << "Failed to open fragment shader!" << endl;

    }

    cout << "Opened fragment shader..." << endl;

    stringstream vertexStream;
    stringstream fragmentStream;

    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();

    vertexCode = vertexStream.str();
    fragmentCode = fragmentStream.str();

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader = 
        compileShader(GL_VERTEX_SHADER, vertexSource);

    unsigned int fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    int success;

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {

        char infolog[512];

        glGetProgramInfoLog(

            ID,
            512,
            nullptr,
            infolog
            
        );

        cout << "Shader program linking failed!" << endl;
        cout << infolog << endl;

    }

    cout << "Shader program linked success..." << endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

unsigned int shader::compileShader(

    unsigned int type,
    const char* source

) {

    unsigned int shader;

    shader = glCreateShader(type);

    glShaderSource(

        shader,
        1,
        &source,
        nullptr

    );

    glCompileShader(shader);

    int success;

    glGetShaderiv(

        shader,
        GL_COMPILE_STATUS,
        &success

    );

    if (!success) {

        char infolog[512];

        glGetShaderInfoLog(

            shader,
            512,
            nullptr,
            infolog

        );

        cout << "Shader compilation failed!" << endl;
        cout << infolog << endl;

    }

    cout << "Shader compilation success!" << endl;

    return shader;

}

void shader::use() {

    glUseProgram(ID);

}

unsigned int shader::getID() const {

    return ID;

}