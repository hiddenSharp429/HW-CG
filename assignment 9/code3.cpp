#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// GLsizei: Non-negative integer type used for sizes
GLsizei winWidth = 400, winHeight = 400;    

// GLfloat: Single-precision floating-point type for colors (range: 0.0 to 1.0)
GLfloat red = 1.0, green = 1.0, blue = 1.0;  // White color (1.0, 1.0, 1.0)

// GLenum: Enumerated type for OpenGL constants
// GL_SMOOTH: Enables Gouraud shading (color interpolation across polygons)
GLenum fillMode = GL_SMOOTH;  

void init(void)
{
    // Sets background color to gray (R=0.6, G=0.6, B=0.6, A=1.0)
    glClearColor(0.6, 0.6, 0.6, 1.0);   
    
    // Switches to projection matrix for setting viewing parameters
    glMatrixMode(GL_PROJECTION);
    // Sets up 2D orthographic viewing region
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void fillOption(GLint selectedOption)
{
    switch(selectedOption) {
        // GL_FLAT: Uses single color for entire polygon (flat shading)
        case 1:  fillMode = GL_FLAT;   break;  
        // GL_SMOOTH: Interpolates colors across polygon (Gouraud shading)
        case 2:  fillMode = GL_SMOOTH; break;  
    }
    // Marks the current window as needing to be redisplayed
    // Triggers a call to the display callback function
    glutPostRedisplay();
}

void displayTriangle(void)
{
    // Clears the color buffer to background color
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Sets the shading model for polygon rendering
    // Either GL_FLAT (constant) or GL_SMOOTH (interpolated) shading
    glShadeModel(fillMode);              
    
    // Sets current color for subsequent vertex specifications
    glColor3f(red, green, blue);         
    
    // Begins specification of vertices for triangles
    // GL_TRIANGLES: Treats each three vertices as an independent triangle
    glBegin(GL_TRIANGLES);
        // Specifies vertex coordinates in 2D integer format
        glVertex2i(280, 20);
        glVertex2i(160, 280);
        // Changes color for the last vertex to pure red
        // In GL_SMOOTH mode: color will be interpolated between vertices
        // In GL_FLAT mode: last vertex color used for entire triangle
        glColor3f(red, 0.0, 0.0);        
        glVertex2i(20, 100);
    glEnd();
    
    // Forces execution of OpenGL commands in finite time
    glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
    // Sets the viewport to cover entire window
    glViewport(0, 0, newWidth, newHeight);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // Resets the projection matrix
    gluOrtho2D(0.0, GLfloat(newWidth), 0.0, GLfloat(newHeight));
    displayTriangle();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Menu Example");
    
    init();
    glutDisplayFunc(displayTriangle);
    
    // Creates a pop-up menu and returns menu ID
    // Parameter: Callback function to handle menu selections
    glutCreateMenu(fillOption);          
    
    // Adds menu entries with associated integer values
    // Parameters: String to display, Value passed to callback
        glutAddMenuEntry("Solid-Color Fill", 1);
        glutAddMenuEntry("Color-Interpolation Fill", 2);
    
    // Associates menu with right mouse button
    // When right button is pressed, menu appears
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // Registers reshape callback function
    glutReshapeFunc(reshapeFcn);
    
    // Enters the GLUT event processing loop
    glutMainLoop();
    return 0;
}