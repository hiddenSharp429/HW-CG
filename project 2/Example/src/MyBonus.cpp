#include "MyBonus.h"

namespace tutorial {
	
	
	MyBonus::MyBonus(std::string id) : cg::Entity(id) {
		
	}
	MyBonus::~MyBonus() {
	}
	
	double MyBonus::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
	
	void MyBonus::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_rand = randomBetween(1,5);
		
		// Link for collision
//		_car = (MyCar*)cg::Registry::instance()->get("Car1");
	}


	
	void MyBonus::update(unsigned long elapsed_millis){
		

		
		switch (_rand) {
			case 1:
				_transx = 120;
				_transy = 1500;
				break;
			case 2:
				_transx = 900;
				_transy = 1620;
				break;
			case 3:
				_transx = 1320;
				_transy = 1200;
				break;
			case 4:
				_transx = 720;
				_transy = 900;
				break;
			case 5:
				_transx = 300;
				_transy = 120;
				break;
		}
	}
	
	
	void MyBonus::draw() {
	
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float diffuse[] = { .0, .0, .9, .5 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glTranslated(_transx,_transy, 7.5);
		glutSolidSphere(15, 20, 20);
		glDisable(GL_BLEND);
		glPopMatrix();

	}
	
	bool MyBonus::isCollision(cg::Vector3d car_position, double car_length) {
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
	
	void MyBonus::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
