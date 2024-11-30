#!/bin/bash
###
 # @Author: hiddenSharp429 z404878860@163.com
 # @Date: 2024-11-28 01:27:29
 # @LastEditors: hiddenSharp429 z404878860@163.com
 # @LastEditTime: 2024-11-30 12:34:22
 # @How to run:
 #  1. `chmod +x code3_compile_and_run.sh`
 #  2. `./code3_compile_and_run.sh`
### 
g++ -o code3 code3.cpp -framework GLUT -framework OpenGL
./code3