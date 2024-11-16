/*
 * @Author: hiddenSharp429 z404878860@163.com
 * @Date: 2024-11-14 12:17:57
 * @LastEditors: hiddenSharp429 z404878860@163.com
 * @LastEditTime: 2024-11-16 15:57:11
 */
#include <GLUT/glut.h> // OpenGL and GLUT headers for Mac OS
#include <math.h> // Include math library for trigonometric functions
#include <unistd.h> // usleep function (microsecond delay)

float angle = 0.0f; // Current rotation angle in degrees
const float radius = 0.5f; // Radius of the circular path that the square will follow
const float PI = 3.14159f;

// Initialize OpenGL settings
void init() {
    // Set the background color to white (R=1.0, G=1.0, B=1.0, A=1.0)
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

// Function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer to start fresh drawing
    
    glPushMatrix(); // Save the current matrix state
    
    // Draw the center point (red dot)
    glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red
    glPointSize(5.0f);            // Set point size
    glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f);   // Draw point at center
    glEnd();
    
    // Draw the circular path (blue circle)
    glColor3f(0.0f, 0.0f, 1.0f);  // Set color to blue
    glBegin(GL_LINE_LOOP);        // Draw continuous line loop
        for(int i = 0; i < 360; i++) {
            float angle = i * PI / 180;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
    
    glTranslatef(0.0f, 0.0f, 0.0f); // Move the coordinate system origin to the center of the window
    
    // Calculate the square's position on the circular path
    float x = radius * cos(angle * PI / 180); // Convert angle from degrees to radians and calculate x coordinate
    float y = radius * sin(angle * PI / 180); // Calculate y coordinate using sine function
    
    glTranslatef(x, y, 0.0f); // Move to the calculated position on the circle
    
    glColor3f(0.0f, 0.0f, 0.0f); // Set the drawing color to black
    
    glBegin(GL_POLYGON); // Begin drawing a filled polygon (square)
        glVertex2f(-0.1f, -0.1f); // Bottom-left vertex
        glVertex2f(0.1f, -0.1f); // Bottom-right vertex
        glVertex2f(0.1f, 0.1f); // Top-right vertex
        glVertex2f(-0.1f, 0.1f); // Top-left vertex
    glEnd(); // End drawing the filled polygon
    
    glPopMatrix(); // Restore the previous matrix state
    
    glutSwapBuffers(); // Swap the back buffer with the front buffer
}

// Animation update function called by glutIdleFunc
void update() {
    angle += 1.0f; // Increment the rotation angle by 1 degree

    // Reset angle when it completes a full rotation (360 degrees)
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    
    usleep(10000); // Pause for 10 milliseconds to control animation speed
    
    glutPostRedisplay(); // Request a redraw of the scene
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT with command line arguments
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set up double buffering and RGB color mode
    
    glutInitWindowSize(500, 500); // Set the initial window size to 500x500 pixels
    
    glutInitWindowPosition(100, 100); // Set the initial window position on the screen
    
    glutCreateWindow("Code1"); // Create a window with a title
    
    init();
    
    glutDisplayFunc(display); // Register the display function to render the scene
    
    glutIdleFunc(update); // Register the update function for continuous animation
    
    glutMainLoop(); // Enter the GLUT event processing loop
    
    return 0;
}