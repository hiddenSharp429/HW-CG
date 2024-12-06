# Screen saver view

## Project Structure
```
project 1/
├── screensaver.cpp    # 跨平台 OpenGL 实现
├── screensaver.h      # 跨平台版本的头文件
├── OpenGLScreenSaverView.m  # macOS 原生实现
├── OpenGLScreenSaverView.h  # macOS 原生版本的头文件
├── Info.plist         # macOS 屏幕保护程序配置
└── Makefile          # 构建脚本
```

## Compiling and Running
- make standalone - 编译跨平台版本（生成可执行文件 screensaver）
- make native - 编译 macOS 原生屏幕保护程序（生成 .saver 包）
- make all - 同时编译两个版本
- make install - 安装 macOS 屏幕保护程序到系统
- make clean - 清理编译产物
- make native install -编译并安装