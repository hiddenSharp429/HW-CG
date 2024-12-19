#include "MyBat.h"

#include <iostream>

namespace tutorial {

	MyBat::MyBat(std::string id) : cg::Entity(id) {
	}
	MyBat::~MyBat(){
	}
	
	// Generate a random number
	double MyBat::randomBetween(double min, double max) {
		return fmod( rand(), ((max-min)+1)) + min;
	}
	
	void MyBat::init() {
		double min_size =
			cg::Properties::instance()->getDouble("MIN_SIZE");
		double max_size =
			cg::Properties::instance()->getDouble("MAX_SIZE");

		_winWidth =
			cg::Manager::instance()->getApp()->getWindow().width;
		_winHeight =
			cg::Manager::instance()->getApp()->getWindow().height;
		_position =
			cg::Vector2d(randomBetween(0,_winWidth),randomBetween(0,_winHeight));
		_size =
			cg::Vector2d(randomBetween(min_size,max_size), randomBetween(min_size,max_size));
		_color =
			cg::Vector3d(randomBetween(0.1,0.9), randomBetween(0.1,0.9), randomBetween(0.1,0.9));



			
		std::ofstream& file =
			cg::DebugFile::instance()->getOutputFileStream();
		file << "Created a bat with size " << _size << "." << std::endl;
	}
	void MyBat::draw() {
		cg::Vector2d min = _position - _size/2.0;
		cg::Vector2d max = _position + _size/2.0;
		glColor3d(0.9,0.9,0.9);
		glLineWidth(1.5);
		glBegin(GL_LINE_LOOP);
			glVertex3d(min[0],min[1], 0);
			glVertex3d(max[0],min[1], 0);
			glVertex3d(max[0],max[1], 0);
			glVertex3d(min[0],max[1], 0);
		glEnd();
	}
	void MyBat::onMouse(int button, int state, int x, int y) {}
	void MyBat::onMouseMotion(int x, int y) {}
	void MyBat::onMousePassiveMotion(int x, int y) {
		_position[0] = x;
		_position[1] = _winHeight - y;
	}
	
	bool MyBat::isCollision(cg::Vector2d box_position, cg::Vector2d box_size) {
		cg::Vector2d bat_bottomleft = _position - _size / 2.0;
		cg::Vector2d bat_topright = _position + _size / 2.0;
		cg::Vector2d box_bottomleft = box_position - box_size / 2.0;
		cg::Vector2d box_topright = box_position + box_size / 2.0;
		return cg::Util::instance()->isAABBoxCollision(
			bat_bottomleft,bat_topright,box_bottomleft,box_topright);
	}

	
}

