cmake_minimum_required(VERSION 3.10)
project(OpenGLScreensaver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

if(WIN32)
    # Windows: Use local GLFW
    set(GLFW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.4.bin.WIN64")
    set(GLFW_INCLUDE_DIR "${GLFW_DIR}/include")
    set(GLFW_LIBRARY "${GLFW_DIR}/lib-vc2022/glfw3.lib")
else()
    # macOS/Linux: Find system GLFW
    find_package(glfw3 REQUIRED)
endif()

# Add executable
add_executable(screensaver screensaver.cpp)

# Include directories
target_include_directories(screensaver PRIVATE 
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

# Link libraries
if(WIN32)
    target_link_libraries(screensaver PRIVATE 
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARY}
    )
    
    # Copy GLFW DLL to output directory (Windows only)
    add_custom_command(TARGET screensaver POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_DIR}/lib-vc2022/glfw3.dll"
        $<TARGET_FILE_DIR:screensaver>
    )
else()
    target_link_libraries(screensaver PRIVATE 
        ${OPENGL_LIBRARIES}
        glfw
    )
endif()
