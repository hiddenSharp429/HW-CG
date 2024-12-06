#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdlib>

float rotation = 0.0f;
float scale = 1.0f;
float scaleDir = 0.001f;
float colors[3] = {1.0f, 0.0f, 0.0f}; // RGB colors
const float PI = 3.14159265359f;
int windowWidth = 800;
int windowHeight = 600;

// Function to change colors smoothly
void updateColors() {
    static float delta[3] = {0.005f, 0.007f, 0.003f};
    for (int i = 0; i < 3; i++) {
        colors[i] += delta[i];
        if (colors[i] >= 1.0f || colors[i] <= 0.0f) {
            delta[i] = -delta[i];
        }
    }
}

// Draw a star using lines
void drawStar(float x, float y, float size) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    
    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++) {
        float angle1 = (72.0f * i - rotation) * PI / 180.0f;
        float angle2 = (72.0f * (i + 2) - rotation) * PI / 180.0f;
        
        float x1 = size * cos(angle1);
        float y1 = size * sin(angle1);
        float x2 = size * cos(angle2);
        float y2 = size * sin(angle2);
        
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
    
    glPopMatrix();
}

// Draw a polygon
void drawPolygon(float x, float y, float size, int sides) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(-rotation * 0.5f, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        float angle = (360.0f / sides * i) * PI / 180.0f;
        float xPos = size * cos(angle);
        float yPos = size * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Center the view
    float aspect = (float)windowWidth / (float)windowHeight;
    if (windowWidth >= windowHeight) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    
    // Update colors
    updateColors();
    
    // Update scale
    scale += scaleDir;
    if (scale > 1.1f || scale < 0.9f) {
        scaleDir = -scaleDir;
    }
    
    // Draw rotating star
    glColor3f(colors[0], colors[1], colors[2]);
    drawStar(0.0f, 0.0f, 0.5f);
    
    // Draw rotating hexagon
    glColor3f(colors[1], colors[2], colors[0]);
    drawPolygon(0.0f, 0.0f, 0.3f, 6);
    
    // Draw points in a circular pattern
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(scale, scale, 1.0f);
    
    glPointSize(3.0f);
    glColor3f(colors[2], colors[0], colors[1]);
    glBegin(GL_POINTS);
    for (int i = 0; i < 36; i++) {
        float angle = (10.0f * i + rotation) * PI / 180.0f;
        float x = 0.7f * cos(angle);
        float y = 0.7f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    
    glPopMatrix();
    
    rotation += 0.5f;
    if (rotation >= 360.0f) {
        rotation -= 360.0f;
    }
    
    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)w / (float)h;
    if (w >= h) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL Screensaver");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
