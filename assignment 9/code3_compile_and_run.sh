#!/bin/bash
###
 # @Author: hiddenSharp429 z404878860@163.com
 # @Date: 2024-12-23 12:34:22
 # @LastEditors: hiddenSharp429 z404878860@163.com
 # @LastEditTime: 2024-12-23 12:34:22
 # @How to run:
 #  1. `chmod +x code3_compile_and_run.sh`
 #  2. `./code3_compile_and_run.sh`
### 
g++ code3.cpp -framework OpenGL -framework GLUT -o code3
./code3