# OpenGL Screensaver

A cross-platform screensaver that displays animated shapes using OpenGL.

## 1.Features
- Draws stars and circles with different colors
- Smooth animations with rotation and movement
- Cross-platform support (Windows and macOS)
- Built using modern C++ and OpenGL
- Fullscreen display with automatic screen resolution adaptation
- Interactive exit with any keyboard input or mouse movement
- Automatic hiding of mouse cursor during runtime

## 2.Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++11 support
- GLFW3
- OpenGL

### Installing Dependencies

#### Windows Quick Installation 
1. Click on `install_env.bat`, which will prompt you to run the setup script as an administrator
2. Wait for the automatic installation to complete (it may take some time)
3. After the installation is complete, the system will automatically configure all necessary environment variables

#### Windows Manual Installation
If the automatic installation script does not work, you can manually install the following components:
1. Install Visual Studio Build Tools: https://visualstudio.microsoft.com/visual-cpp-build-tools/
2. Install CMake: https://cmake.org/download/
3. Install glfw-3.4.bin.WIN64: https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip extract to `./deps/`

#### macOS
```bash
brew install cmake glfw
```

## 3.Building

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
#cmake .. -G "Visual Studio 17 2022" -A x64
```

3. Build the project:
```bash
cmake --build .
```

## 4.Running
After building, run the screensaver:
For Windows:
```bash
./start_screensaver.bat
```
For macOS:
```bash
./start_screensaver.sh
```

## 5.Controls
- Press any key or move the mouse to exit the screensaver
- The mouse cursor will be automatically hidden during runtime

## 6.License
This project is open source and available under the MIT License.
