# OpenGL Screensaver

A cross-platform screensaver that displays animated shapes using OpenGL.

## Features
- Draws stars and circles with different colors
- Smooth animations with rotation and movement
- Cross-platform support (Windows and macOS)
- Built using modern C++ and OpenGL

## Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++11 support
- GLFW3
- OpenGL

### Installing Dependencies

#### macOS
```bash
brew install cmake glfw
```

#### Windows
1. Install CMake from https://cmake.org/download/
2. Install GLFW using vcpkg:
```bash
vcpkg install glfw3:x64-windows
```

## Building

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

## Running
After building, run the screensaver:
```bash
./screensaver
```

## Controls
- Press ESC to exit the screensaver

## License
This project is open source and available under the MIT License.
