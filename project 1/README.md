# OpenGL Screensaver

A cross-platform screensaver that displays animated shapes using OpenGL.

跨平台屏保，使用OpenGL绘制动画形状

## 1.Features
- Draws stars and circles with different colors/绘画不同颜色的星星和圆圈
- Smooth animations with rotation and movement/旋转和移动的平滑动画
- Cross-platform support (Windows and macOS)/跨平台支持（Windows和macOS）
- Built using modern C++ and OpenGL/使用现代C++和OpenGL
- Fullscreen display with automatic screen resolution adaptation/全屏显示，自动适配屏幕分辨率
- Interactive exit with any keyboard input or mouse movement/任何键盘输入或鼠标移动都可以退出
- Automatic hiding of mouse cursor during runtime/运行时自动隐藏鼠标光标


## 2.Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++11 support
- GLFW3
- OpenGL

### Installing Dependencies

#### Windows [Quick Installation]
1. Click on `install_env.bat`, which will prompt you to run the setup script as an administrator/
点击`install_env.bat`,它将提示你以管理员身份运行安装脚本

2. Wait for the automatic installation to complete (it may take some time)/等待自动安装完成（可能需要一些时间）
3. After the installation is complete, the system will automatically configure all necessary environment variables/安装完成后，系统将自动配置所有必要的环境变量

#### Windows [Manual Installation]
If the automatic installation script does not work, you can manually install the following components:/
如果自动安装脚本无法工作，你可以手动安装以下组件：
1. Install Visual Studio Build Tools/安装Visual Studio构建工具: https://visualstudio.microsoft.com/visual-cpp-build-tools/
2. Install CMake/安装CMake: https://cmake.org/download/
3. Install glfw-3.4.bin.WIN64: https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip extract to `./deps/`/安装glfw并解压到`./deps/`

#### macOS
```bash
brew install cmake glfw
```

## 3.Building

1. Create a build directory/创建构建目录:
```bash
mkdir build
cd build
```

2. Generate build files/生成构建文件:
```bash
cmake ..
#cmake .. -G "Visual Studio 17 2022" -A x64
```

3. Build the project/构建项目:
```bash
cmake --build .
```

## 4.Running
After building, run the screensaver/运行屏保:

For Windows:
```bash
./start_screensaver.bat
```
For macOS:
```bash
./start_screensaver.sh
```

## 5.Controls
- Press any key or move the mouse to exit the screensaver/按任意键或移动鼠标退出屏保
- The mouse cursor will be automatically hidden during runtime/运行时鼠标光标将自动隐藏
