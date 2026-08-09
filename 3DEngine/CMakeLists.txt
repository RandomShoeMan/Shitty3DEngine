cmake_minimum_required(VERSION 3.20)

project(3DEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3DEngine
    main.cpp
    renderer/Shader.cpp
    renderer/camera.cpp
    math/Vec3.cpp
    math/Mat4.cpp
    external/glad/src/gl.c
)

target_include_directories(3DEngine PRIVATE
    C:/msys64/ucrt64/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

target_link_directories(3DEngine PRIVATE
    C:/msys64/ucrt64/lib
)

target_link_libraries(3DEngine
    glfw3
    opengl32
)