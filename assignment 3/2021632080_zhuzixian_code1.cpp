/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2024-10-26 09:13:15
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2024-10-26 10:51:58
 * @FilePath: /C++/CG/code1.cpp
 * @Description: assignment 3 code 1
 * @How to complite it:g++ -std=c++11 -o code1 code1.cpp -framework GLUT -framework OpenGL
 * @How to run it:./code1
 */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>
#include <vector>
#include <string>


// 数据点结构
struct DataPoint {
    float x, y;
    std::string label;
};

// 月份数据
std::vector<DataPoint> data = {
    {0, 0.8, "Jan"}, {1, 0.6, "Feb"}, {2, 0.5, "Mar"}, {3, 0.45, "Apr"},
    {4, 0.5, "May"}, {5, 0.3, "Jun"}, {6, 0.2, "Jul"}, {7, 0.1, "Aug"},
    {8, 0.15, "Sep"}, {9, 0.2, "Oct"}, {10, 0.4, "Nov"}, {11, 0.9, "Dec"}
};

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawPoint(float x, float y) {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.7f, 1.0f);  // 浅蓝色

    // 绘制折线
    for (size_t i = 1; i < data.size(); ++i) {
        drawLine(data[i-1].x / 11.0 * 1.8 - 0.9, data[i-1].y, 
                 data[i].x / 11.0 * 1.8 - 0.9, data[i].y);
    }

    // 绘制数据点
    for (const auto& point : data) {
        drawPoint(point.x / 11.0 * 1.8 - 0.9, point.y);
    }

    // 绘制x轴标签
    glColor3f(0.5f, 0.5f, 0.5f);  // 灰色
    for (const auto& point : data) {
        drawText(point.x / 11.0 * 1.8 - 0.9, -0.05, point.label.c_str());
    }

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // 白色背景
    gluOrtho2D(-1.0, 1.0, -0.1, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Code1 Chart");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}