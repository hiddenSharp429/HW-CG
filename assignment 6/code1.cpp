#include <GLUT/glut.h>
#include <string.h>

GLfloat scaleFactor = 1.0;    // Scaling factor
GLfloat scaleStep = 0.01;     // Scaling step
GLboolean isAutoScale = true; // Auto-scaling flag
GLboolean isScalingOut = false; // Scaling out flag

class wcPt2D {
   public:
      GLfloat x, y;
};

void renderText(float x, float y, const char *text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);  // Fixed coordinate system for text
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(0.0, 0.0, 0.0);  // Black text
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void init (void)
{
   /* Set color for clearing display window to white. */
   glClearColor (1.0, 1.0, 1.0, 0.0);

   /* Set parameters for world-coordinate clipping window. */
   glMatrixMode (GL_PROJECTION);
   gluOrtho2D (-100.0 * scaleFactor, 100.0 * scaleFactor, 
              -100.0 * scaleFactor, 100.0 * scaleFactor);

   /* Set mode for constructing geometric transformation matrix. */
   glMatrixMode (GL_MODELVIEW);
}

void triangle (wcPt2D *verts)
{
   GLint k;

   glBegin (GL_TRIANGLES);
      for (k = 0; k < 3; k++)
         glVertex2f (verts [k].x, verts [k].y);
   glEnd ();
}

void timer(int value) {
    if (isAutoScale) {
        if (isScalingOut) {
            scaleFactor += scaleStep;
            if (scaleFactor >= 2.0) isScalingOut = false;
        } else {
            scaleFactor -= scaleStep;
            if (scaleFactor <= 0.5) isScalingOut = true;
        }
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-100.0 * scaleFactor, 100.0 * scaleFactor, 
                   -100.0 * scaleFactor, 100.0 * scaleFactor);
        glMatrixMode(GL_MODELVIEW);
        
        glutPostRedisplay();
    }
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case ' ':   // Spacebar toggle auto-scaling
            isAutoScale = !isAutoScale;
            break;
        case 'i':   // scaling out (zoom in)
            if (!isAutoScale) {
                scaleFactor *= 0.8;  
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(-100.0 * scaleFactor, 100.0 * scaleFactor, 
                          -100.0 * scaleFactor, 100.0 * scaleFactor);
                glMatrixMode(GL_MODELVIEW);
                glutPostRedisplay();
            }
            break;
        case 'o':   // scaling in (zoom out)
            if (!isAutoScale) {
                scaleFactor *= 1.25;  
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(-100.0 * scaleFactor, 100.0 * scaleFactor, 
                          -100.0 * scaleFactor, 100.0 * scaleFactor);
                glMatrixMode(GL_MODELVIEW);
                glutPostRedisplay();
            }
            break;
    }
}

void displayFcn (void)
{
    /* Define initial position for triangle.*/
    wcPt2D verts [3] = { {-50.0, -25.0}, {50.0, -25.0}, {0.0, 50.0}}; 
    
    glClear (GL_COLOR_BUFFER_BIT);    // Clear display window.         
    
    // Left viewport
    glViewport (0, 0, 300, 300);     // Set left viewport.   
    
    // Set up projection for triangle
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0 * scaleFactor, 100.0 * scaleFactor, 
              -100.0 * scaleFactor, 100.0 * scaleFactor);
    glMatrixMode(GL_MODELVIEW);
    
    glColor3f(0.0, 0.0, 1.0);  // Blue triangle
    triangle (verts);           // Display triangle.             
    
    // Render text with fixed position
    renderText(10, 280, "Space: Auto/Manual");
    renderText(10, 260, "i/o: Zoom in/out");
    
    /* Rotate triangle and display in right half of display window. */ 
    glColor3f (1.0, 0.0, 0.0);           // Set fill color to red.     
    glViewport (300, 0, 300, 300);        // Set right viewport.        
    
    // Set up projection for triangle
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0 * scaleFactor, 100.0 * scaleFactor, 
              -100.0 * scaleFactor, 100.0 * scaleFactor);
    glMatrixMode(GL_MODELVIEW);
    
    glRotatef (90.0, 0.0, 0.0, 1.0);     // Rotate about z axis.       
    triangle (verts);            // Display red rotated triangle.
    
    glFlush ();
}

int main (int argc, char ** argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition (50, 50);
   glutInitWindowSize (600, 300);
   glutCreateWindow ("Split-Screen Example");

   init ();
   glutDisplayFunc (displayFcn);
   glutKeyboardFunc(keyboard);   // Add keyboard callback 
   glutTimerFunc(0, timer, 0);   // Add timer callback

   glutMainLoop ();
   return 0;
}