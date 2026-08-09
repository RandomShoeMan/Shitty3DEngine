#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "renderer/shader.h"
#include "renderer/camera.h"
#include "math/Vec3.h"
#include "math/Mat4.h"

using namespace std;

int main() {

    if (!glfwInit()) {

        cout << "Failed to initialize GLFW!" << endl;
        
        return -1;

    }

    cout << "GLFW Initialised!" << endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "3D Engine",
        nullptr,
        nullptr

    );

    if (!window) {

        cout << "Failed to create a window!" << endl;

        glfwTerminate();

        return -1;

    }

    cout << "Window Created!" << endl;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {

        cout << "Failed to initialise GLAD!" << endl;

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;

    }

    cout << "Initialised OpenGL: " << glGetString(GL_VERSION) << endl;

    shader shader(

        "shaders/basic.vert",
        "shaders/basic.frag"

    );

    float vertices[] = {

        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f

    };

    Vec3 point(1.0f, 0.0f, 0.0f);
    
    Vec3 position(2.0f, 3.0f, 4.0f);

    float angle = 3.14159265f / 4.0f;

    Mat4 scale = Mat4::scale(

        Vec3(2.0f, 2.0f, 2.0f)

    );

    Mat4 rotation = Mat4::rotationY(angle);

    Mat4 translation = Mat4::translation(position);

    Mat4 model = translation * rotation * scale;

    Vec3 result = model * point;

    camera camera(

        Vec3(2.0f, 0.0f, 3.0f),
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3(0.0f, 1.0f, 0.0f)
    
    );

    Mat4 view = camera.getViewMatrix();

    for (int row = 0; row < 4; row++) {

        for (int column = 0; column < 4; column++) {

            cout << view.data[row][column] << " ";

        }

        cout << endl;
        
    }



    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(

        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW

    );

    glVertexAttribPointer(

        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0

    );

    glEnableVertexAttribArray(0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();

        glBindVertexArray(VAO);

        glDrawArrays(

            GL_TRIANGLES,
            0,
            3

        );

        GLenum error = glGetError();

        if (error != GL_NO_ERROR) {

            cout << "OpenGL Error: " << error << endl;

        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    cout << "Window Closing! Goodbye." << endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}