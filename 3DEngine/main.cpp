#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "renderer/shader.h"
#include "renderer/camera.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "loader/objLoader.h"

using namespace std;

int main() {

    OBJLoader loader;

    loader.load("models/humanMan.obj");

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL(glfwGetProcAddress)) {

        cout << "Failed to initialise GLAD!" << endl;

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;

    }

    cout << "Initialised OpenGL: " << glGetString(GL_VERSION) << endl;

    glEnable(GL_DEPTH_TEST);

    shader shader(

        "shaders/basic.vert",
        "shaders/basic.frag"

    );

    camera camera(Vec3(0.0f, 0.0f, 3.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f));

    Mat4 projection = Mat4::perspective(3.14159265f / 3.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    float angle = 0.0f;

    double lastTime = glfwGetTime();
    int frames = 0;

    float playerSpeed = 0.001f;
    float cameraSensitivity = 0.002f;

    double mouseX;
    double mouseY;

    double lastMouseX = 640.0;
    double lastMouseY = 360.0;

    bool wireframeCheck = true;
    bool f3PressCheck = false;

    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        loader.vertices.size() * sizeof(Vec3),
        loader.vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vec3),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    unsigned int EBO;

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        loader.indices.size() * sizeof(unsigned int),
        loader.indices.data(),
        GL_STATIC_DRAW
    );

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

            camera.moveForward(playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

            camera.moveForward(-playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

            camera.moveRight(playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

            camera.moveRight(-playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

            camera.moveUp(playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

            camera.moveUp(-playerSpeed);

        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

            cout << "Window Closing! Goodbye." << endl;

            glfwDestroyWindow(window);
            glfwTerminate();

            return 0;

        }

        bool f3Pressed = glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS;

        if (f3Pressed && !f3PressCheck) {

            wireframeCheck = !wireframeCheck;

            if (wireframeCheck) {

                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            } else {

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            }

        }

        f3PressCheck = f3Pressed;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        double deltaX = mouseX - lastMouseX;
        double deltaY = mouseY - lastMouseY;

        camera.setRotationY(-deltaX * cameraSensitivity);
        camera.setRotationX(-deltaY * cameraSensitivity);

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        Mat4 view = camera.getViewMatrix();

        angle += 0.0001f;

        Mat4 model =
        Mat4::translation(Vec3(0.0f, 0.0f, -3.0f));
        //Mat4::rotationY(angle) *
        //Mat4::rotationX(angle);

        Mat4 mvp = projection * view * model;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMat4("uMVP", mvp);

        glBindVertexArray(VAO);

        glDrawElements(
            GL_TRIANGLES,
            loader.indices.size(),
            GL_UNSIGNED_INT,
            0
        );

        glfwSwapBuffers(window);
        glfwPollEvents();

        frames++;

        double currentTime = glfwGetTime();

        if (currentTime - lastTime >= 1.0) {

            cout << "FPS: " << frames << endl;

            frames = 0;

            lastTime = currentTime;

        }

    }

    cout << "Window Closing! Goodbye." << endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}