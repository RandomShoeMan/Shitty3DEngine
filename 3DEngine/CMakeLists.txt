cmake_minimum_required(VERSION 3.20)

project(3DEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# Source files
# --------------------------------------------------

add_executable(3DEngine

    main.cpp

    renderer/Shader.cpp
    renderer/camera.cpp

    math/Vec3.cpp
    math/Vec4.cpp
    math/Mat4.cpp

    loader/objLoader.cpp

    external/glad/src/gl.c
)

# --------------------------------------------------
# Include directories
# --------------------------------------------------

target_include_directories(3DEngine PRIVATE

    external/glad/include

)

# --------------------------------------------------
# Link libraries
# --------------------------------------------------

target_link_libraries(3DEngine

    glfw3
    opengl32

)

# --------------------------------------------------
# Copy GLFW DLL
# --------------------------------------------------

add_custom_command(TARGET 3DEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

    "C:/msys64/ucrt64/bin/glfw3.dll"

    "$<TARGET_FILE_DIR:3DEngine>/glfw3.dll"

)

# --------------------------------------------------
# Copy MinGW runtime DLLs
# --------------------------------------------------

add_custom_command(TARGET 3DEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

    "C:/msys64/ucrt64/bin/libgcc_s_seh-1.dll"

    "$<TARGET_FILE_DIR:3DEngine>/libgcc_s_seh-1.dll"

)

add_custom_command(TARGET 3DEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

    "C:/msys64/ucrt64/bin/libstdc++-6.dll"

    "$<TARGET_FILE_DIR:3DEngine>/libstdc++-6.dll"

)

add_custom_command(TARGET 3DEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different

    "C:/msys64/ucrt64/bin/libwinpthread-1.dll"

    "$<TARGET_FILE_DIR:3DEngine>/libwinpthread-1.dll"

)