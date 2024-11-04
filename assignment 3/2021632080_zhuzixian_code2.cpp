/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2024-10-26 09:29:32
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2024-10-26 10:51:48
 * @FilePath: /C++/CG/code2.cpp
 * @Description: assignment 3 code 2
 * @How to complite it:g++ -std=c++11 -o code2 code2.cpp -framework GLUT -framework OpenGL
 * @How to run it:./code2
 */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>

const int NUM_SEGMENTS = 12; // 圆被分成的段数
const float PI = 3.14159265358979323846f;

void drawCircleWithLines() {
    glColor3f(0.0f, 0.7f, 1.0f);  // 设置颜色为浅蓝色

    // 绘制圆周
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        float theta = i * PI / 180;
        glVertex2f(cos(theta), sin(theta));
    }
    glEnd();

    // 绘制从圆心到圆周的线段
    glBegin(GL_LINES);
    for(int i = 0; i < NUM_SEGMENTS; i++) {
        float theta = i * 2 * PI / NUM_SEGMENTS;
        glVertex2f(0, 0);  // 圆心
        glVertex2f(cos(theta), sin(theta));  // 圆周上的点
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircleWithLines();
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 设置背景为白色
    gluOrtho2D(-1.1, 1.1, -1.1, 1.1);  // 设置坐标系
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Circle with Lines");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}