#include "MyObstacle.h"

namespace tutorial {
	
	
	MyObstacle::MyObstacle(std::string id, double transx, double transy) : cg::Entity(id) {
		_transx = transx;
		_transy = transy;
	}
	MyObstacle::~MyObstacle() {
	}
	void MyObstacle::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;;
		
		// Link for collision
//		_car = (MyCar*)cg::Registry::instance()->get("Car1");
	}

	void MyObstacle::draw() {
	
		// Static obstacle
		float diffuse[] = { .0, .0, .9, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glPushMatrix();
		glLineWidth(3.5);
		glTranslated(_transx, _transy, 12.5);
		glutSolidSphere(25, 20, 20);
		glPopMatrix();

	}
	
	void MyObstacle::update(unsigned long elapsed_millis){}
	
	bool MyObstacle::isCollision(cg::Vector3d car_position, double car_length) {
		cg::Vector2d obs_bottomleft, obs_topright, car_bottomleft, car_topright;
		obs_bottomleft[0] = _transx - 10;
		obs_bottomleft[1] = _transy - 10;
		obs_topright[0] = _transx + 10;
		obs_topright[1] = _transy + 10;
		car_bottomleft[0] = car_position[0] - car_length / 2.0 + 5;
		car_bottomleft[1] = car_position[1] - car_length / 2.0 + 5;
		car_topright[0] = car_position[0] + car_length / 2.0 - 5;
		car_topright[1] = car_position[1] + car_length / 2.0 - 5;
		return cg::Util::instance()->isAABBoxCollision(obs_bottomleft,obs_topright,car_bottomleft,car_topright);
	}
	
	void MyObstacle::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
