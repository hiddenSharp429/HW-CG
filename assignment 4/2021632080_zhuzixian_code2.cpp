/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2024-11-04 09:49:06
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2024-11-04 10:45:10
 */
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>
#include <cmath>
#include <cstdlib>

void init() {
    glClearColor(0.2, 0.1, 0.3, 0.0); // 改为深紫色背景，模拟日出/日落时的天空
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// 绘制单个云朵
void drawCloud(float centerX, float centerY, float size) {
    float points[][2] = {
        {-3, 0.5}, {-2.8, 0.7}, {-2.5, 0.8}, {-2.2, 0.8}, {-2, 0.7}, 
        {-1.7, 0.6}, {-1.4, 0.5}, {-1, 0.4}, {-0.5, 0.3}, {0, 0.3}, 
        {0.5, 0.3}, {1, 0.4}, {1.4, 0.5}, {1.7, 0.6}, {2, 0.7},
        {2.2, 0.8}, {2.5, 0.8}, {2.8, 0.7}, {3, 0.5}
    };
    
    // 上层（亮部分）- 使用黄色和橙色的渐变
    for(int layer = 0; layer < 10; layer++) {
        float pointSize = (10 - layer) * 2.0;
        float alpha = 1.0;
        
        glPointSize(pointSize * size);
        glBegin(GL_POINTS);
        
        for(int i = 0; i < 19; i++) {
            // 使用黄色到橙色的渐变
            float red = 1.0;
            float green = 0.8 - layer * 0.05; 
            float blue = 0.2 - layer * 0.02;  
            glColor4f(red, green, blue, alpha);
            
            float offsetX = (rand() % 10 - 5) * 0.05;
            float offsetY = (rand() % 10 - 5) * 0.05;
            
            float x = centerX + (points[i][0] + offsetX) * size * 15;
            float y = centerY + (points[i][1] + offsetY) * size * 15;
            glVertex2f(x, y);
            
            for(int j = 0; j < 3; j++) {
                float extraOffsetX = (rand() % 20 - 10) * 0.05;
                float extraOffsetY = (rand() % 20 - 10) * 0.05;
                glVertex2f(x + extraOffsetX * size * 10, y + extraOffsetY * size * 10);
            }
        }
        glEnd();
    }
    
    // 下层（阴影部分）- 使用深红色和暗橙色
    for(int layer = 0; layer < 3; layer++) {
        float pointSize = (6 - layer) * 2.5;
        float alpha = 0.25 - layer * 0.15;
        
        glPointSize(pointSize * size);
        glBegin(GL_POINTS);
        
        for(int i = 0; i < 19; i++) {
            // 使用深红色调
            float red = 0.7 - layer * 0.1;    // 从0.8逐渐降低
            float green = 0.3 - layer * 0.05;  // 从0.3逐渐降低
            float blue = 0.1 - layer * 0.02;   // 从0.1逐渐降低
            glColor4f(red, green, blue, alpha);
            
            float offsetX = (rand() % 10 - 5) * 0.03;
            float offsetY = (rand() % 10 - 5) * 0.03;
            
            float shadowOffset = 1.0 + layer * 0.7;
            float x = centerX + (points[i][0] + offsetX + shadowOffset * 0.5) * size * 15;
            float y = centerY + (points[i][1] - shadowOffset + offsetY) * size * 15;
            glVertex2f(x, y);
            
            for(int j = 0; j < 3; j++) {
                float extraOffsetX = (rand() % 20 - 10) * 0.05;
                float extraOffsetY = (rand() % 20 - 10) * 0.05;
                glVertex2f(x + extraOffsetX * size * 10, y + extraOffsetY * size * 10);
            }
        }
        glEnd();
    }
}

// 绘制太阳
void drawSun(float centerX, float centerY, float radius) {
    // 绘制太阳主体
    glColor4f(1.0, 0.90, 0.0, 1.0); 
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++) {
        float angle = i * 3.14159 / 180;
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
    
    // 绘制太阳光芒
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for(int i = 0; i < 12; i++) {
        float angle = i * 30 * 3.14159 / 180;
        float x1 = centerX + cos(angle) * radius;
        float y1 = centerY + sin(angle) * radius;
        float x2 = centerX + cos(angle) * (radius * 1.5);
        float y2 = centerY + sin(angle) * (radius * 1.5);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSun(50, 600, 30);  // 在左上角添加太阳
    drawCloud(200, 450, 1.5);  // 左上方的云
    drawCloud(600, 500, 1.8);  // 右上方的云
    drawCloud(400, 400, 2.2);  // 中间的云
    drawCloud(300, 480, 0.8);  // 小云朵
    drawCloud(500, 420, 0.9);  // 小云朵
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sunset");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}