#include "MyCamera.h"

namespace tutorial {

    MyCamera::MyCamera() : Entity("Camera") {
	}
    MyCamera::~MyCamera() {
	}
    void MyCamera::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_numplayers = 0;
		
		// Links for camera position
		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");

    }
    void MyCamera::draw() {

        // Camera 
		glViewport(0,0, _winWidth,_winHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//		glOrtho(0,_winWidth,0,_winHeight,0,-100);
        gluPerspective(45,_winWidth/_winHeight,1,_winWidth*2);
//		glTranslated(-_car->_position[0], -_car->_position[1], 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	
    
        // eye z position changed from _winWidth/1.5 to 600/1.5 so the view distance doesn't increase when the window is resized
		if(_numplayers == 1)
			gluLookAt(_car1->_position[0], _car1->_position[1]-500, 600, _car1->_position[0],_car1->_position[1],0, 0,1,0);
		else
			gluLookAt((_car1->_position[0]+_car2->_position[0])/2, (_car1->_position[1]+_car2->_position[1])/2-500, 600, (_car1->_position[0]+_car2->_position[0])/2,(_car1->_position[1]+_car2->_position[1])/2,0, 0,1,0);


		// Light
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_NORMALIZE);
		//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		//glEnable(GL_COLOR_MATERIAL);
		
		GLfloat lightpos[] = {1, 1, 1, 0};		// Eye coordinates
//		GLfloat lightpos[] = {600, 600, 50, 1};		// Eye coordinates
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);	// light moves with the car if the light is not set after all the viewing/modeling transformations
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.000001);


//		Rotates the whole scene? I only need to set the eyeposition in gluLookAt as a lower y-coordinate than the center position (so the eye doesn't point directly down) to make the scene look rotated
//		glRotated(-80, 1, 0, 0);
		
		//glColor3d(0.0,0.7,0.0);
		//glPushMatrix();
		//glTranslated(500,0,-11);
		//glScaled(2500,2500,1);
		//glutSolidCube(1);		// Background
		//glPopMatrix();

		

    }
    
	void MyCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}    
}
