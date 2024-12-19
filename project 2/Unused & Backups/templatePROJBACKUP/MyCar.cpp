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
		width = cg::Properties::instance()->getDouble("CAR_WIDTH");		// largura do carro (eixo xx) - horizontal
		length = cg::Properties::instance()->getDouble("CAR_LENGTH");	// comprimento do carro (eixo yy) - vertical
		height = cg::Properties::instance()->getDouble("CAR_HEIGHT");	// altura do carro (eixo zz) - profundidade(não perceptível)
		// Creates car
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_position = cg::Properties::instance()->getDouble("CAR_INITIAL_POS");
		_size = cg::Vector3d(width, length, height);
		_color = cg::Vector3d(randomBetween(0.1,0.9),randomBetween(0.1,0.9),randomBetween(0.1,0.9));
		_angle = 0;
		_acceleration = 0;
		_velocity = 0;

		
		
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
		
		if(_velocity == 0)
			_acceleration = 0;
				
				
		if (isUpKeyPressed()) {
			setDownKeyReleased(false);
			if(_acceleration <= 200)
				_acceleration++;
			if(_velocity < 0)
				_velocity += 2*_acceleration * elapsed_seconds;
			if(_velocity < 500)
				_velocity += _acceleration * elapsed_seconds;

		}
		
		
		if (isLeftKeyPressed()) {
			_angle++;
		}
		if (isRightKeyPressed()) {
			_angle--;
		}		

		if (isDownKeyPressed()) {
			setUpKeyReleased(false);
			if(_acceleration <= 200)
				_acceleration++;
			if(_velocity > 0)
				_velocity += 2*-_acceleration * elapsed_seconds;
			if(_velocity > -500)
				_velocity += -_acceleration * elapsed_seconds;

		}
		
		if (isDownKeyReleased()) {
			if(_velocity >= 0)		// The effect of releasing the down key (deacceleration of reverse) is no longer needed since the car has stopped
				setDownKeyReleased(false);
			if(_acceleration <= 200)
				_acceleration++;

			_velocity += _acceleration * elapsed_seconds;

		}
		
		
		
		if (isUpKeyReleased()) {
			if(_velocity <= 0)		// The effect of releasing the up key (deacceleration) is no longer needed since the car has stopped
				setUpKeyReleased(false);
			if(_acceleration <= 200)
				_acceleration++;

			_velocity += -_acceleration * elapsed_seconds;

		}
		
		_position[0] += _velocity * elapsed_seconds;
		_position[1] += _velocity * elapsed_seconds;
				
		// Appear on the opposite side of the window
		if(_position[1] > _winHeight/2)
			_position[1] = -_winHeight/2;
		if(_position[1] < -_winHeight/2)
			_position[1] = _winHeight/2;
		if(_position[0] > _winWidth/2)
			_position[0] = -_winWidth/2;
		if(_position[0] < -_winWidth/2)
			_position[0] = _winWidth/2;




		// If car gets to the window limits, respawn at the center
/*		if((_position[0] < -_winWidth/2) || (_position[0] > _winWidth/2) || (_position[1] < -_winHeight/2) || (_position[1] > _winHeight/2)) { 
			_position[0] = 0.0;
			_position[1] = 0.0;
			_velocity[0] = 0.0;
			_velocity[1] = 0.0;

		}
*/


	}	// UPDATE
	
	
	
	void MyCar::draw() {

	/*	cg::Vector3d minrot = _rotation - _size/2.0;	????????
		cg::Vector3d maxrot = _rotation + _size/2.0;	*/
		glColor3dv(_color.get());
		glPushMatrix();
		glTranslated(_position[0], _position[1], 0);
		glTranslated(_winWidth/2, _winHeight/2, 0);		// Car is created at the center of the window
		glRotated(_angle, 0, 0, 1);
		glTranslated(-_position[0],-_position[1], 0);
		glBegin(GL_QUADS);
			glVertex3d(-width/2,-length/2, 0);
			glVertex3d(width/2,-length/2, 0);
			glVertex3d(width/2,length/2, 0);
			glVertex3d(-width/2,length/2, 0);
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
