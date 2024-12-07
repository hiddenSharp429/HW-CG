cmake_minimum_required(VERSION 3.10)
project(OpenGLScreensaver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Add executable
add_executable(screensaver screensaver.cpp)

# Link libraries
target_link_libraries(screensaver
    OpenGL::GL
    glfw
)
