@echo off
cd /d "%~dp0"
if not exist "build" (
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022" -A x64
    cmake --build .
) else (
    cd build
)

echo Starting screensaver...
.\Debug\screensaver.exe
pause
