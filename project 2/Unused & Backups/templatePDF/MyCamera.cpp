#include "MyCamera.h"

#include <iostream>

namespace tutorial {

	MyCamera::MyCamera() : Entity("MyCamera") {}
	MyCamera::~MyCamera() {}
	void MyCamera::init() {
	
	_winWidth = cg::Manager::instance()->getApp()->getWindow().width;
	_winHeight = cg::Manager::instance()->getApp()->getWindow().height;

	}
	void MyCamera::draw() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,_winWidth,0,_winHeight,0,-100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
}
