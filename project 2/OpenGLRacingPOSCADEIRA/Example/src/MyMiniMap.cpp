#include "MyMiniMap.h"

namespace tutorial {
	
	
	MyMiniMap::MyMiniMap(std::string id) : cg::Entity(id) {
	}
	MyMiniMap::~MyMiniMap() {
	}
	
	void MyMiniMap::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;

		_cam = (MyCamera*)cg::Registry::instance()->get("Camera");

		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");

	}

	void MyMiniMap::update(unsigned long elapsed_millis) {
        

	}

	void MyMiniMap::drawOverlay() {
//		float specular[] = { .0f, .0f, .0f, 1.0f };
//		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//		float fDiffuse[] = {0.8f, 0.8f, 0.8f, 1.f};
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse);
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();


//		
//		glDisable(GL_LIGHTING);

//        // Camera 
//		glViewport(_winWidth-_winWidth/2-_winWidth/8,0, _winWidth/4,_winHeight/4);
// 		float specular5[] = { .0, .0, .0, 1.0 };
//		glMaterialfv(GL_FRONT, GL_SPECULAR, specular5);
//		float fDiffuse5[] = {0.f, 0.f, 0.f, .25f};
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse5);
//				
//		glPushMatrix();
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glColor4d(0.0,0.0,0.0, .25);
//		glTranslated(_winWidth/2-_winWidth/4,0,0);		// Big box to make the laggy text fit
//		glScaled( _winWidth,_winHeight,1);
//		glutSolidCube(1);
//		glDisable(GL_BLEND);
//		glPopMatrix();
//		glOrtho(0,1800,0,1800,0,-100);
//        //gluPerspective(45,_winWidth/_winHeight,1,_winWidth*2);
//		
//		
//		//glEnable(GL_SCISSOR_TEST);
//		//glEnable(GL_DEPTH_TEST);

//		glMatrixMode(GL_MODELVIEW);
//		//glScissor(0,0, 200,200);
//		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//		//glLoadIdentity();
//		

//		//glPushAttrib( GL_LIGHTING_BIT | GL_CURRENT_BIT );

//		glColor3d(1.0,1.0,1.0);

//		_track = (MyTrack*)cg::Registry::instance()->get("Track");
//		_track->draw();

//		
//		// Don't draw obstacles nor bonuses so players don't know where they are! muahaha

//		
//		_car1->_minimapMode = true;
//		_car1->draw();
//		_car1->_minimapMode = false;
//		
//		if(_car2->state.isEnabled()) {
//			_car2->_minimapMode = true;
//			_car2->draw();
//			_car2->_minimapMode = false;
//		}

//		//glPopAttrib();
//		//glDisable(GL_SCISSOR_TEST);
//		//glFlush();
//		//glutSwapBuffers();
//		glEnable(GL_LIGHTING);
//		//glDisable(GL_DEPTH_TEST);
	}
	
	
	void MyMiniMap::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
	
}
