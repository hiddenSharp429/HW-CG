#include "MyCar.h"

namespace tutorial {

	MyCar::MyCar(std::string id) : cg::Entity(id) {
	}
	MyCar::~MyCar() {
	}
	
	cg::Vector3d MyCar::getPosition() {
		return _position;
	}
	void MyCar::setPosition( int coord) {
	}

	

	
	double MyCar::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}
	

	void MyCar::init() {
		// Read from property file
		double width = cg::Properties::instance()->getDouble("CAR_WIDTH");		// largura do carro (eixo xx) - horizontal
		double length = cg::Properties::instance()->getDouble("CAR_LENGTH");	// comprimento do carro (eixo yy) - vertical
		double height = cg::Properties::instance()->getDouble("CAR_HEIGHT");	// altura do carro (eixo zz) - profundidade(não perceptível)
		// Creates car
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_position = cg::Properties::instance()->getDouble("CAR_INITIAL_POS");
		_rotation = cg::Vector3d(0, 0, 1);		// O carro só roda em z
		_size = cg::Vector3d(width, length, height);
		_color = cg::Vector3d(randomBetween(0.1,0.9),randomBetween(0.1,0.9),randomBetween(0.1,0.9));


		
		
		_upKeyPressed = false;
		_leftKeyPressed = false;
		_rightKeyPressed = false;
		_downKeyPressed = false;
		_upKeyReleased = false;
		_leftKeyReleased = false;
		_rightKeyReleased = false;
		_downKeyReleased = false;		
	}
	
	void MyCar::update(unsigned long elapsed_millis) {

		double elapsed_seconds = elapsed_millis / 1000.0;
		
		if(_velocity == (0,0,0))
			_acceleration = (0,0,0);
				
				
		if (isUpKeyPressed()) {
			setDownKeyReleased(false);
			if((_acceleration[0] <= 200))
				_acceleration[0]++;
			if(_acceleration[1] <= 200)
				_acceleration[1]++;
			if(_velocity[0] < 0)
				_velocity[0] += 2*_acceleration[0] * elapsed_seconds;
			if(_velocity[1] < 0)
				_velocity[1] += 2*_acceleration[1] * elapsed_seconds;
			if(_velocity[0] < 500)
				_velocity[0] += _acceleration[0] * elapsed_seconds;
			if(_velocity[1] < 500)
				_velocity[1] += _acceleration[1] * elapsed_seconds;
			_position[0] += _velocity[0] * elapsed_seconds*sin(_angle);
			_position[1] += _velocity[1] * elapsed_seconds*cos(_angle);
		}
		
		
		if (isLeftKeyPressed()) {
			_angle++;
		}
		if (isRightKeyPressed()) {
			_angle--;
		}		

		if (isDownKeyPressed()) {
			setUpKeyReleased(false);
			if(_acceleration[1] <= 200)
				_acceleration[1]++;
			if(_velocity[1] > 0)
				_velocity[1] += 2*-_acceleration[1] * elapsed_seconds;
			if(_velocity[1] > -500)
				_velocity[1] += -_acceleration[1] * elapsed_seconds;
			_position[1] += _velocity[1] * elapsed_seconds;

		}
		
		if (isDownKeyReleased()) {
			if(_velocity[1] >= 0)		// The effect of releasing the down key (deacceleration of reverse) is no longer needed since the car has stopped
				setDownKeyReleased(false);
			if(_acceleration[1] <= 200)
				_acceleration[1]++;

			_velocity[1] += _acceleration[1] * elapsed_seconds;
			_position[1] += _velocity[1] * elapsed_seconds;			

		}
		
		
		
		if (isUpKeyReleased()) {
			if(_velocity[1] <= 0)		// The effect of releasing the up key (deacceleration) is no longer needed since the car has stopped
				setUpKeyReleased(false);
			if(_acceleration[1] <= 200)
				_acceleration[1]++;

			_velocity[1] += -_acceleration[1] * elapsed_seconds;
			_position[1] += _velocity[1] * elapsed_seconds;			

		}
		
		
				
		// Appear on the opposite side of the window (y only)
		if(_position[1] > _winHeight/2)
			_position[1] = -_winHeight/2;
		if(_position[1] < -_winHeight/2)
			_position[1] = _winHeight/2;


		// If car gets to the window limits, respawn at the center
/*		if((_position[0] < -_winWidth/2) || (_position[0] > _winWidth/2) || (_position[1] < -_winHeight/2) || (_position[1] > _winHeight/2)) { 
			_position[0] = 0.0;
			_position[1] = 0.0;
			_velocity[0] = 0.0;
			_velocity[1] = 0.0;

		}
*/
	}
	
	void MyCar::draw() {
		cg::Vector3d min = _position - _size/2.0;
		cg::Vector3d max = _position + _size/2.0;
	/*	cg::Vector3d minrot = _roation - _size/2.0;	????????
		cg::Vector3d maxrot = _rotation + _size/2.0;	*/
		glColor3dv(_color.get());
		glPushMatrix();
		glTranslated(_winWidth/2, _winHeight/2, 0);		// Car is created at the center of the window
		glTranslated(_position[0], _position[1], 0);		// Car is created at the center of the window
		glRotated(_angle, _rotation[0], _rotation[1], _rotation[2]);
		glTranslated(-_position[0],-_position[1], 0);		// Car is created at the center of the window
		glBegin(GL_QUADS);
			glVertex3d(min[0],min[1], 0);
			glVertex3d(max[0],min[1], 0);
			glVertex3d(max[0],max[1], 0);
//			glVertex3d(0, max[1]+10,0);
			glVertex3d(min[0],max[1], 0);
		glEnd();
		glPopMatrix();

		
	}
	
	bool MyCar::isUpKeyPressed() {
		return _upKeyPressed;
	}
	void MyCar::setUpKeyPressed(bool val) {
		_upKeyPressed = val;
	}
	bool MyCar::isUpKeyReleased() {
		return _upKeyReleased;
	}
	void MyCar::setUpKeyReleased(bool val) {
		_upKeyReleased = val;
	}
	
	
	bool MyCar::isLeftKeyPressed() {
		return _leftKeyPressed;
	}
	void MyCar::setLeftKeyPressed(bool val) {
		_leftKeyPressed = val;
	}
	bool MyCar::isLeftKeyReleased() {
		return _leftKeyReleased;
	}
	void MyCar::setLeftKeyReleased(bool val) {
		_leftKeyReleased = val;
	}
	
	
	bool MyCar::isRightKeyPressed() {
		return _rightKeyPressed;
	}
	void MyCar::setRightKeyPressed(bool val) {
		_rightKeyPressed = val;
	}
	bool MyCar::isRightKeyReleased() {
		return _rightKeyReleased;
	}
	void MyCar::setRightKeyReleased(bool val) {
		_rightKeyReleased = val;
	}
	
	
	bool MyCar::isDownKeyPressed() {
		return _downKeyPressed;
	}
	void MyCar::setDownKeyPressed(bool val) {
		_downKeyPressed = val;
	}
	bool MyCar::isDownKeyReleased() {
		return _downKeyReleased;
	}
	void MyCar::setDownKeyReleased(bool val) {
		_downKeyReleased = val;
	}
	

	
	

}
