#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

// 动画状态
struct AnimationState {
    float rotation;        // 旋转角度
    float colors[3];      // RGB 颜色值
    float colorDeltas[3]; // 颜色变化速度
};

// 函数声明
void init(void);
void display(void);
void reshape(int w, int h);
void timer(int value);
void drawStar(void);
void drawHexagon(void);
void drawPoints(void);
void updateColors(void);

#endif // SCREENSAVER_H
