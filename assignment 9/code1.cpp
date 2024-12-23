#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLsizei winWidth = 400, winHeight = 300;    // Initial display-window size.

void init(void)
{
    // Sets the color used when clearing the window.
    // Parameters: (red, green, blue, alpha), each in range [0.0, 1.0]
    glClearColor(0.0, 0.0, 1.0, 1.0);   
    
    // Specifies which matrix stack is the target for subsequent matrix operations
    // GL_PROJECTION: Specifies projection transformation matrix
    glMatrixMode(GL_PROJECTION);

    // Sets up a 2D orthographic viewing region
    // Parameters: (left, right, bottom, top)
    // Coordinates for viewing the window contents
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void displayFcn(void)
{
    // Clears the specified buffer to preset values
    // GL_COLOR_BUFFER_BIT: Indicates the buffers currently enabled for color writing
    glClear(GL_COLOR_BUFFER_BIT);        

    // Sets the current color for drawing operations
    // Parameters: (red, green, blue) each in range [0.0, 1.0]
    glColor3f(1.0, 0.0, 0.0);           

    // Specifies the diameter of points in pixels
    // Parameter: diameter
    glPointSize(3.0);                    
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    // Defines the viewport dimensions
    // Parameters: (x, y, width, height)
    // Specifies the lower-left corner of viewport and its dimensions in pixels
    glViewport(0, 0, newWidth, newHeight);

    // Switch to projection matrix stack
    glMatrixMode(GL_PROJECTION);

    // Replaces current matrix with the identity matrix
    // Resets the current matrix to initial state
    glLoadIdentity();

    // Establishes new clipping volume dimensions
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    
    winWidth = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
    // Delimits the vertices of a primitive or group of primitives
    // GL_POINTS: Treats each vertex as a single point
    glBegin(GL_POINTS);
        // Specifies a vertex with 2 integer coordinates
        // Parameters: (x, y)
        glVertex2i(x, y);
    glEnd();  // Marks the end of vertex data
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        plotPoint(xMouse, winHeight - yMouse);
    
    // Forces execution of OpenGL functions in finite time
    // Ensures all previous OpenGL commands complete rendering
    glFlush();
}

int main(int argc, char** argv)
{
    // Initializes GLUT and processes any command line arguments
    glutInit(&argc, argv);

    // Specifies the display mode to be used for the window
    // GLUT_SINGLE: Single buffer display mode
    // GLUT_RGB: RGB color mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Sets the initial position of the window
    // Parameters: pixels from left and top of screen
    glutInitWindowPosition(100, 100);

    // Sets the initial size of the window
    // Parameters: width and height in pixels
    glutInitWindowSize(winWidth, winHeight);

    // Creates a window with specified title
    glutCreateWindow("Mouse Plot Points");
    
    init();

    // Registers callback function to display graphics
    glutDisplayFunc(displayFcn);

    // Registers callback function for window reshape events
    glutReshapeFunc(winReshapeFcn);

    // Registers callback function for mouse events
    glutMouseFunc(mousePtPlot);
    
    // Enters the GLUT event processing loop
    // Application will remain in this loop until program termination
    glutMainLoop();
    return 0;
}