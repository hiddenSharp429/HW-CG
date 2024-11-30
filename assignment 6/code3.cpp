
#include <GLUT/glut.h>
#include <iostream>
using namespace std;

// Define region codes for Cohen-Sutherland algorithm
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Define clipping window coordinates
const float x_min = 100.0;
const float x_max = 400.0;
const float y_min = 100.0;
const float y_max = 400.0;

// Structure to represent a 2D point
struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

// Function to compute region code for a point
int computeCode(Point p) {
    int code = INSIDE;
    
    if (p.x < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (p.x > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (p.y < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (p.y > y_max)  // above the rectangle
        code |= TOP;
    
    return code;
}

// Cohen-Sutherland line clip algorithm
bool cohenSutherlandClip(Point& p1, Point& p2) {
    // Compute region codes for P1, P2
    int code1 = computeCode(p1);
    int code2 = computeCode(p2);
    bool accept = false;
    
    while (true) {
        // If both endpoints lie within rectangle
        if ((code1 | code2) == 0) {
            accept = true;
            break;
        }
        // If both endpoints are outside rectangle
        else if (code1 & code2) {
            break;
        }
        // Some segment lies within the rectangle
        else {
            int code_out;
            Point p;
            
            // Pick outside point
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;
            
            // Find intersection point using formulas
            // y = y1 + slope * (x - x1)
            // x = x1 + (1/slope) * (y - y1)
            if (code_out & TOP) {
                p.x = p1.x + (p2.x - p1.x) * (y_max - p1.y) / (p2.y - p1.y);
                p.y = y_max;
            }
            else if (code_out & BOTTOM) {
                p.x = p1.x + (p2.x - p1.x) * (y_min - p1.y) / (p2.y - p1.y);
                p.y = y_min;
            }
            else if (code_out & RIGHT) {
                p.y = p1.y + (p2.y - p1.y) * (x_max - p1.x) / (p2.x - p1.x);
                p.x = x_max;
            }
            else if (code_out & LEFT) {
                p.y = p1.y + (p2.y - p1.y) * (x_min - p1.x) / (p2.x - p1.x);
                p.x = x_min;
            }
            
            // Replace point outside rectangle with intersection point
            if (code_out == code1) {
                p1 = p;
                code1 = computeCode(p1);
            }
            else {
                p2 = p;
                code2 = computeCode(p2);
            }
        }
    }
    return accept;
}

// Sample lines for testing
Point lines[][2] = {
    {Point(50, 50), Point(450, 450)},
    {Point(300, 50), Point(300, 450)},
    {Point(50, 300), Point(450, 300)},
    {Point(0, 0), Point(500, 500)},
    {Point(10, 400), Point(490, 20)},
};
const int numLines = 5;

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw clipping rectangle
    glColor3f(0.0, 0.0, 1.0);  // Blue
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();
    
    // Process and draw all lines
    for (int i = 0; i < numLines; i++) {
        Point p1 = lines[i][0];
        Point p2 = lines[i][1];
        
        // Draw original line in light gray
        glColor3f(0.7, 0.7, 0.7);  // Light gray
        glBegin(GL_LINES);
        glVertex2f(lines[i][0].x, lines[i][0].y);
        glVertex2f(lines[i][1].x, lines[i][1].y);
        glEnd();
        
        // If line can be clipped, draw the clipped portion in green
        if (cohenSutherlandClip(p1, p2)) {
            glColor3f(0.0, 1.0, 0.0);  // Green
            glBegin(GL_LINES);
            glVertex2f(p1.x, p1.y);
            glVertex2f(p2.x, p2.y);
            glEnd();
        }
    }
    
    glFlush();
}

// Initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}