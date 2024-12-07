@echo off
title OpenGL Screensaver Environment Setup

:: 创建日志文件
set "LOGFILE=%~dp0install_log.txt"
echo Installation started at %date% %time% > "%LOGFILE%"

echo ====================================
echo OpenGL Screensaver Environment Setup
echo ====================================
echo.
echo The installation process will be logged to: %LOGFILE%
echo.
echo Press any key to start installation...
pause > nul

:: 检查管理员权限
echo Checking administrator privileges... >> "%LOGFILE%"
NET FILE 1>NUL 2>NUL
if '%errorlevel%' == '0' (
    goto START
) else (
    echo Requesting administrative privileges...
    echo Requesting administrative privileges... >> "%LOGFILE%"
    goto ELEVATE
)

:ELEVATE
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
set params = %*:"=""
echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params%", "", "runas", 1 >> "%temp%\getadmin.vbs"
echo Launching UAC prompt... >> "%LOGFILE%"
"%temp%\getadmin.vbs"
del "%temp%\getadmin.vbs"
exit /B

:START
echo Administrator privileges confirmed. >> "%LOGFILE%"
echo.
echo Step 1: Installing Chocolatey...
echo Step 1: Installing Chocolatey... >> "%LOGFILE%"

:: 创建临时批处理文件来执行后续命令
set "TEMP_BATCH=%TEMP%\continue_install.bat"
echo @echo off > "%TEMP_BATCH%"
echo set "LOGFILE=%LOGFILE%" >> "%TEMP_BATCH%"

:: 检查 Chocolatey 是否已安装
where choco >nul 2>&1
if %errorlevel% neq 0 (
    powershell -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" >> "%LOGFILE%" 2>&1
    if errorlevel 1 (
        echo Failed to install Chocolatey. Check %LOGFILE% for details.
        echo Failed to install Chocolatey at %date% %time% >> "%LOGFILE%"
        pause
        exit /b 1
    )
    echo Chocolatey installed successfully.
    echo Chocolatey installed successfully at %date% %time% >> "%LOGFILE%"
)

:: 将剩余的安装步骤写入临时批处理文件
echo echo Step 2: Installing Visual Studio Build Tools... >> "%TEMP_BATCH%"
echo echo Step 2: Installing Visual Studio Build Tools... ^>^> "%%LOGFILE%%" >> "%TEMP_BATCH%"
echo C:\ProgramData\chocolatey\bin\choco install visualstudio2022buildtools --package-parameters "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended" -y ^>^> "%%LOGFILE%%" 2^>^&1 >> "%TEMP_BATCH%"

echo echo Step 3: Installing CMake... >> "%TEMP_BATCH%"
echo echo Step 3: Installing CMake... ^>^> "%%LOGFILE%%" >> "%TEMP_BATCH%"
echo C:\ProgramData\chocolatey\bin\choco install cmake -y ^>^> "%%LOGFILE%%" 2^>^&1 >> "%TEMP_BATCH%"

echo echo Step 4: Installing Git... >> "%TEMP_BATCH%"
echo echo Step 4: Installing Git... ^>^> "%%LOGFILE%%" >> "%TEMP_BATCH%"
echo C:\ProgramData\chocolatey\bin\choco install git -y ^>^> "%%LOGFILE%%" 2^>^&1 >> "%TEMP_BATCH%"

echo echo Step 5: Downloading and setting up GLFW... >> "%TEMP_BATCH%"
echo echo Step 5: Downloading and setting up GLFW... ^>^> "%%LOGFILE%%" >> "%TEMP_BATCH%"
echo mkdir deps 2^>nul >> "%TEMP_BATCH%"
echo cd deps >> "%TEMP_BATCH%"
echo powershell -Command "Invoke-WebRequest -Uri 'https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip' -OutFile 'glfw.zip'" ^>^> "%%LOGFILE%%" 2^>^&1 >> "%TEMP_BATCH%"
echo powershell -Command "Expand-Archive -Path 'glfw.zip' -DestinationPath '.' -Force" ^>^> "%%LOGFILE%%" 2^>^&1 >> "%TEMP_BATCH%"
echo del glfw.zip >> "%TEMP_BATCH%"
echo cd .. >> "%TEMP_BATCH%"

echo echo. >> "%TEMP_BATCH%"
echo echo ==================================== >> "%TEMP_BATCH%"
echo echo Installation completed successfully! >> "%TEMP_BATCH%"
echo echo Please restart your computer to ensure all changes take effect. >> "%TEMP_BATCH%"
echo echo ==================================== >> "%TEMP_BATCH%"
echo echo Installation completed at %%date%% %%time%% ^>^> "%%LOGFILE%%" >> "%TEMP_BATCH%"
echo echo. >> "%TEMP_BATCH%"
echo pause >> "%TEMP_BATCH%"

:: 启动新的命令提示符来执行剩余的安装步骤
echo Starting new command prompt to continue installation...
start "OpenGL Screensaver Setup" cmd /c "%TEMP_BATCH%"
exit
