#include "MyObstacle2.h"

namespace tutorial {
	
	
	MyObstacle2::MyObstacle2(std::string id, double posx, double posy) : cg::Entity(id) {
		_posx = posx;
		_posy = posy;
	}
	MyObstacle2::~MyObstacle2() {
	}
	void MyObstacle2::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_positionx = 0;
		_sentido = true;
		
		// Links for collisions
		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");
	}

	void MyObstacle2::update(unsigned long elapsed_millis){

		double elapsed_seconds = elapsed_millis / 1000.0;


		if( (_positionx < 0) || (_positionx >= 100) )
			_sentido = !_sentido;

		if(_sentido)
			_positionx += 75 * elapsed_seconds;
		else
			_positionx -= 75 * elapsed_seconds;
		
		
	}

	void MyObstacle2::draw() {
		
		//Moving obstacle
		float diffuse[] = { .0, 0., .9, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glPushMatrix();
		glTranslated(_posx, _posy, 25);
		glTranslated(_positionx,0, 0);
		glRotated(90,0,1,0);
		glutSolidCone(10, 50, 20, 20);
		glPopMatrix();

	}
	
	
	bool MyObstacle2::isCollision(cg::Vector3d car_position, double car_length) {
		cg::Vector2d obs_bottomleft, obs_topright, car_bottomleft, car_topright;
		obs_bottomleft[0] = _posx+_positionx;
		obs_bottomleft[1] = _posy;
		obs_topright[0] = _posx+_positionx+50;
		obs_topright[1] = _posy+20;
		car_bottomleft[0] = car_position[0] - car_length / 2.0;
		car_bottomleft[1] = car_position[1] - car_length / 2.0;
		car_topright[0] = car_position[0] + car_length / 2.0;
		car_topright[1] = car_position[1] + car_length / 2.0;
		return cg::Util::instance()->isAABBoxCollision(obs_bottomleft,obs_topright,car_bottomleft,car_topright);
	}
	
	void MyObstacle2::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}

}
