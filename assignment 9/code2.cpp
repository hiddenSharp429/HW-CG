#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Window size parameters
GLsizei winWidth = 400, winHeight = 300;    // GLsizei is a non-negative integer type

void init(void)
{
    // Sets the color used when clearing the window
    // Parameters (R,G,B,A): blue color with full opacity
    glClearColor(0.0, 0.0, 1.0, 1.0);   
    
    // Sets current matrix mode to projection matrix stack
    // GL_PROJECTION: Used for setting viewing and clipping parameters
    glMatrixMode(GL_PROJECTION);

    // Sets up a 2D orthographic viewing region
    // Parameters: left, right, bottom, top coordinates of viewing volume
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void displayFcn(void)
{
    // Clears the frame buffer
    // GL_COLOR_BUFFER_BIT: Indicates the buffers currently enabled for color writing
    glClear(GL_COLOR_BUFFER_BIT);        

    // Sets current drawing color to red (R=1, G=0, B=0)
    // Parameters: red, green, blue components in range [0.0, 1.0]
    glColor3f(1.0, 0.0, 0.0);           

    // Sets the width of points to be drawn
    // Parameter: width in pixels (must be > 0.0)
    glPointSize(3.0);                    
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    // Sets the viewport dimensions within the window
    // Parameters: lower-left corner (x,y) and width, height in pixels
    glViewport(0, 0, newWidth, newHeight);

    // Switches to projection matrix stack for viewing volume adjustments
    glMatrixMode(GL_PROJECTION);

    // Resets the current projection matrix to identity matrix
    // Must be called before setting new projection parameters
    glLoadIdentity();

    // Establishes new clipping volume dimensions matching window size
    // Parameters cast to GLdouble for precise floating-point coordinates
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    
    winWidth = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
    // Begins definition of a set of geometric primitives
    // GL_POINTS: Each vertex is treated as a single point
    glBegin(GL_POINTS);
        // Specifies a vertex with integer coordinates
        // Parameters: x and y coordinates in window space
        glVertex2i(x, y);
    // Ends geometric-primitive definition
    glEnd();
}

/* Keyboard callback function for curve drawing */
void curveDrawing(GLubyte curvePlotKey, GLint xMouse, GLint yMouse)
{
    // GLubyte: 8-bit unsigned char for key codes
    // xMouse, yMouse: cursor position when key is pressed
    GLint x = xMouse;
    // Convert window coordinates to OpenGL coordinates
    // OpenGL's origin is bottom-left, window coordinates' origin is top-left
    GLint y = winHeight - yMouse;
    
    switch(curvePlotKey)
    {
        case 'c':  // When 'c' key is pressed
            plotPoint(x, y);
            break;
        default:
            break;
    }
    // Forces immediate execution of OpenGL commands
    // Necessary for single-buffered applications
    glFlush();
}

int main(int argc, char** argv)
{
    // Initializes GLUT library and processes command line arguments
    glutInit(&argc, argv);

    // Sets display mode properties
    // GLUT_SINGLE: Single buffer display mode
    // GLUT_RGB: RGB color mode (vs. color index mode)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Sets initial window position on screen
    // Parameters: pixels from left and top of screen
    glutInitWindowPosition(100, 100);

    // Sets initial window size in pixels
    glutInitWindowSize(winWidth, winHeight);

    // Creates window with specified title
    glutCreateWindow("Keyboard Curve-Drawing Example");
    
    init();

    // Registers display callback function
    glutDisplayFunc(displayFcn);

    // Registers reshape callback function
    // Called when window is resized
    glutReshapeFunc(winReshapeFcn);

    // Registers keyboard callback function
    // Called when a key is pressed and window has focus
    glutKeyboardFunc(curveDrawing);
    
    // Enters GLUT's main event processing loop
    // Program remains in this loop until terminated
    glutMainLoop();
    return 0;
}