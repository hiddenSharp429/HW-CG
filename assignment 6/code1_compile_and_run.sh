#!/bin/bash
###
 # @Author: hiddenSharp429 z404878860@163.com
 # @Date: 2024-11-28 01:20:21
 # @LastEditors: hiddenSharp429 z404878860@163.com
 # @LastEditTime: 2024-11-30 11:45:12
 # @How to run:
 #  1. `chmod +x code1_compile_and_run.sh`
 #  2. `./code1_compile_and_run.sh`
### 
g++ -o code1 code1.cpp -framework GLUT -framework OpenGL
./code1