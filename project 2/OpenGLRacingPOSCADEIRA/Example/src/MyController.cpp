#include "MyController.h"

namespace tutorial {

	
	MyController::MyController() : cg::Entity("Controller") {
	}

	
	MyController::~MyController() {
	}
	void MyController::init() {
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
				
		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");	
		_ballObstacle1 = (MyObstacle*)cg::Registry::instance()->get("BallObstacle1");
		_ballObstacle2 = (MyObstacle*)cg::Registry::instance()->get("BallObstacle2");
		_ballObstacle3 = (MyObstacle*)cg::Registry::instance()->get("BallObstacle3");
		_movingObstacle1 = (MyObstacle2*)cg::Registry::instance()->get("MovingObstacle1");
		_cam = (MyCamera*)cg::Registry::instance()->get("Camera");
		
		_piecesize = cg::Properties::instance()->getDouble("TRACKPIECE_SIZE");

		_car1width = _car1->width;
		_car1length = _car1->length;
		_car2width = _car2->width;
		_car2length = _car2->length;


	}

	void MyController::update(unsigned long elapsed_millis){
		
		
		// Sensors that activate obstacle2 when the car is on them & pitstop sensor to repair the car's damage
		cg::Vector2d sensor_bottomleft, sensor_topright, sensor2_bottomleft, sensor2_topright, pitstop_bottomleft, pitstop_topright, car1_bottomleft, car1_topright, car2_bottomleft, car2_topright;
		sensor_bottomleft[0] = _piecesize;
		sensor_bottomleft[1] = (_piecesize*3);
		sensor_topright[0] = (_piecesize*2);
		sensor_topright[1] = (_piecesize*4);
		sensor2_bottomleft[0] = _piecesize;
		sensor2_bottomleft[1] = (_piecesize*4);
		sensor2_topright[0] = (_piecesize*2);
		sensor2_topright[1] = (_piecesize*5);
		pitstop_bottomleft[0] = 0;
		pitstop_bottomleft[1] = (_piecesize*2);
		pitstop_topright[0] = _piecesize;
		pitstop_topright[1] = (_piecesize*4);
		car1_bottomleft[0] = _car1->_position[0] - _car1->length / 2.0;
		car1_bottomleft[1] = _car1->_position[1] - _car1->length / 2.0;
		car1_topright[0] = _car1->_position[0] + _car1->length / 2.0;
		car1_topright[1] = _car1->_position[1] + _car1->length / 2.0;
		car2_bottomleft[0] = _car2->_position[0] - _car2->length / 2.0;
		car2_bottomleft[1] = _car2->_position[1] - _car2->length / 2.0;
		car2_topright[0] = _car2->_position[0] + _car2->length / 2.0;
		car2_topright[1] = _car2->_position[1] + _car2->length / 2.0;
		if( (cg::Util::instance()->isAABBoxCollision(sensor_bottomleft,sensor_topright,car1_bottomleft,car1_topright)) || (cg::Util::instance()->isAABBoxCollision(sensor2_bottomleft,sensor2_topright,car1_bottomleft,car1_topright))
		||	(cg::Util::instance()->isAABBoxCollision(sensor_bottomleft,sensor_topright,car2_bottomleft,car2_topright)) || (cg::Util::instance()->isAABBoxCollision(sensor2_bottomleft,sensor2_topright,car2_bottomleft,car2_topright)))
			_movingObstacle1->state.enable();
		else {
			_movingObstacle1->state.disable();
			_movingObstacle1->_positionx = 0;		// Reset obstacle's position
		}
		
		
		// Collision detection  (obstacle2 has to be enabled, ie, if it is hidden (no sensor touched), the car can't collide with it)
		if((_ballObstacle1->isCollision(_car1->_position,_car1->length)) || (_ballObstacle2->isCollision(_car1->_position,_car1->length))
		|| (_ballObstacle3->isCollision(_car1->_position,_car1->length)) || ((_movingObstacle1->isCollision(_car1->_position,_car1->length)) && (_movingObstacle1->state.isEnabled())) ) {
			_car1->_velocity = -_car1->_velocity;
			_car1->_colliding = true;
			if(_car1->_velocity < 0 )					// If the velocity was positive before, means I was going forward, so..
				_car1->setDownKeyReleased(true);		// ..after inverting the velocity, I go backwards and need the deacceleration of reverse effect
			else
				_car1->setUpKeyReleased(true);			// If it was negative , now I'm going forward and so I need the deacceleration effect
		}
		else
			if(_car1->_colliding) {
				if(_car1->_damageBonus)
					_car1->_dano++;
				else
					_car1->_dano += 2;				// so incrementa o dano qnd o carro deixar de colidir (evita caso do carro "preso" no obstaculo)
				_car1->_colliding = false;
			}
			
		// Collision detection  (obstacle2 has to be enabled, ie, if it is hidden (no sensor touched), the car can't collide with it)
		if((_ballObstacle1->isCollision(_car2->_position,_car2->length)) || (_ballObstacle2->isCollision(_car2->_position,_car2->length))
		|| (_ballObstacle3->isCollision(_car1->_position,_car1->length)) || ((_movingObstacle1->isCollision(_car2->_position,_car2->length)) && (_movingObstacle1->state.isEnabled())) ) {
			_car2->_velocity = -_car2->_velocity;
			_car2->_colliding = true;
			if(_car2->_velocity < 0 )					// If the velocity was positive before, means I was going forward, so..
				_car2->setDownKeyReleased(true);		// ..after inverting the velocity, I go backwards and need the deacceleration of reverse effect
			else
				_car2->setUpKeyReleased(true);			// If it was negative , now I'm going forward and so I need the deacceleration effect
		}
		else
			if(_car2->_colliding) {
				if(_car2->_damageBonus)
					_car2->_dano++;
				else
					_car2->_dano += 2;				// so incrementa o dano qnd o carro deixar de colidir (evita caso do carro "preso" no obstaculo)
				_car2->_colliding = false;
			}
		
		
		
		
		
		_car1angle = _car1->_angle;
		_car2angle = _car2->_angle;

//			_car1bottomleft[0] = -_car1width/2*sin((-_car1angle*3.14)/180)+_car1->_position[0];
			_car1bottomleft[0] = _car1->_position[0]+cos((_car1angle*3.14)/180)*-_car1width/2-sin((_car1angle*3.14)/180)*-_car1length/2;
			_car1bottomleft[1] = _car1->_position[1]+sin((_car1angle*3.14)/180)*-_car1width/2+cos((_car1angle*3.14)/180)*-_car1length/2;
			_car1bottomright[0] =  _car1->_position[0]+cos((_car1angle*3.14)/180)*+_car1width/2-sin((_car1angle*3.14)/180)*-_car1length/2;
			_car1bottomright[1] = _car1->_position[1]+sin((_car1angle*3.14)/180)*+_car1width/2+cos((_car1angle*3.14)/180)*-_car1length/2;
			_car1topright[0] =  _car1->_position[0]+cos((_car1angle*3.14)/180)*+_car1width/2-sin((_car1angle*3.14)/180)*+_car1length/2;
			_car1topright[1] = _car1->_position[1]+sin((_car1angle*3.14)/180)*+_car1width/2+cos((_car1angle*3.14)/180)*+_car1length/2;
			_car1topleft[0] =  _car1->_position[0]+cos((_car1angle*3.14)/180)*-_car1width/2-sin((_car1angle*3.14)/180)*+_car1length/2;
			_car1topleft[1] = _car1->_position[1]+sin((_car1angle*3.14)/180)*-_car1width/2+cos((_car1angle*3.14)/180)*+_car1length/2;

			_car2bottomleft[0] = _car2->_position[0]+cos((_car2angle*3.14)/180)*-_car2width/2-sin((_car2angle*3.14)/180)*-_car2length/2;
			_car2bottomleft[1] = _car2->_position[1]+sin((_car2angle*3.14)/180)*-_car2width/2+cos((_car2angle*3.14)/180)*-_car2length/2;
			_car2bottomright[0] = _car2->_position[0]+cos((_car2angle*3.14)/180)*+_car2width/2-sin((_car2angle*3.14)/180)*-_car2length/2;
			_car2bottomright[1] = _car2->_position[1]+sin((_car2angle*3.14)/180)*+_car2width/2+cos((_car2angle*3.14)/180)*-_car2length/2;
			_car2topright[0] = _car2->_position[0]+cos((_car2angle*3.14)/180)*+_car2width/2-sin((_car2angle*3.14)/180)*+_car2length/2;
			_car2topright[1] = _car2->_position[1]+sin((_car2angle*3.14)/180)*+_car2width/2+cos((_car2angle*3.14)/180)*+_car2length/2;
			_car2topleft[0] = _car2->_position[0]+cos((_car2angle*3.14)/180)*-_car2width/2-sin((_car2angle*3.14)/180)*+_car2length/2;
			_car2topleft[1] = _car2->_position[1]+sin((_car2angle*3.14)/180)*-_car2width/2+cos((_car2angle*3.14)/180)*+_car2length/2;
			
			std::vector<cg::Vector2d> _car2position, _car1position;
			
			_car2position.push_back(_car2bottomleft);
			_car2position.push_back(_car2bottomright);
			_car2position.push_back(_car2topright);
			_car2position.push_back(_car2topleft);
			
			_car1position.push_back(_car1bottomleft);
			_car1position.push_back(_car1bottomright);
			_car1position.push_back(_car1topright);
			_car1position.push_back(_car1topleft);

			// Car hits car
			if( ( (cg::Util::instance()->isPointInPolygon(_car1bottomleft, _car2position)) || (cg::Util::instance()->isPointInPolygon(_car1bottomright, _car2position)) || (cg::Util::instance()->isPointInPolygon(_car1topright, _car2position)) || (cg::Util::instance()->isPointInPolygon(_car1topleft, _car2position)) 
			||	(cg::Util::instance()->isPointInPolygon(_car2bottomleft, _car1position)) || (cg::Util::instance()->isPointInPolygon(_car2bottomright, _car1position)) || (cg::Util::instance()->isPointInPolygon(_car2topright, _car1position)) || (cg::Util::instance()->isPointInPolygon(_car2topleft, _car1position)) )
			&& _car1->state.isEnabled() && _car2->state.isEnabled() ) {
				
					if(abs(_car1->_velocity) > abs(_car2->_velocity)) {
						//_car1->_collisionAngle = 0;
						//_car2->_colliding = true;
						_car2->_collisionAngle = _car1angle;
						_car2->_collisionVelocity = _car1->_velocity;
						if(_car2->_velocity >= 0)
							_car2->setUpKeyReleased(true);
						else
							_car2->setDownKeyReleased(true);
					}
					else {
						//_car2->_collisionAngle = 0;
						//_car1->_colliding = true;
						_car1->_collisionAngle = _car2angle;
						_car1->_collisionVelocity = _car2->_velocity;
						if(_car1->_velocity >= 0)
							_car1->setUpKeyReleased(true);
						else
							_car1->setDownKeyReleased(true);
					}

				
			}
			
			if(_cam->_numplayers == 2) {
				updatePoints( _car1, _car2);
				updatePoints( _car2, _car1);
			}

	}

	void MyController::updatePoints(MyCar* first, MyCar* second) {
		
		bool _update = false;
		
		switch (first->_coordx) {
			
			case 0 : {
				switch (first->_coordy) {
					case 0 : {
						if( (first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) || (first->_position[1]-_winHeight+100 > second->_position[1]) ) {
							_update = true;
						}
						break;
					}
					case 1 : {
						if( ( first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) || ( first->_position[1]-_winHeight+100 > second->_position[1]) ) {
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) || ( first->_position[1]-_winHeight+100 > second->_position[1]) ) {
							_update = true;
						}
						break;
					}
					case 5 : {
						if( ( first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) || ( first->_position[1]-_winHeight+100 > second->_position[1] ) ) {
							_update = true;
						}
						break;
					}
				}
				break;
			}
				
			case 1 : {
				switch (first->_coordy) {
					case 0 : {
						if( first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) {
							_update = true;
						}
						break;
					}
					case 1 : {
						if( ( first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) || ( first->_position[1]-_winHeight+100 > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 2 : {
						if( (first->_position[1]-_winHeight+100) > second->_position[1] ) {
							_update = true;
						}
						break;
					}
					case 3 : {
						if( (first->_position[1]-_winHeight+100) > second->_position[1] ) {
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) || ( first->_position[1]-_winHeight+100 > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 5 : {
						if( first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) {
							_update = true;
						}
						break;
					}
				}
				break;
			}
			case 2 : {
				switch (first->_coordy) {
					case 0 : {
						if( first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) {
							_update = true;
						}
						break;
					}
					case 1 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) || ( first->_position[1] < second->_position[1]-_winHeight+100 ) ) {
							_update = true;
						}
						break;
					}
					case 2 : {
						if( first->_position[1] < second->_position[1]-_winHeight+100 ) {
							_update = true;
						}
						break;
					}
					case 3 : {
						if( first->_position[1] < second->_position[1]-_winHeight+100 ) {
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) || ( first->_position[1] < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 5 : {
						if( first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) {
							_update = true;
						}
						break;
					}
				}
				break;
			}
			case 3 : {
				switch (first->_coordy) {
					case 0 : {
						if( (first->_position[0] < second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 ) || ( first->_position[1] < second->_position[1]-_winHeight+100) ){
							_update = true;
						}
						break;
					}
					case 1 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > second->_position[0] ) || ( first->_position[1] < second->_position[1]-_winHeight+100) ){
							_update = true;
						}
						break;
					}
					case 2 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]-_winHeight+100) > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 3 : {
						if( (first->_position[1]-_winHeight+100) > second->_position[1] ) {
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]-_winHeight+100) > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 5 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > (second->_position[0])) ) {
							_update = true;
						}
						break;
					}
				}
				break;
			}
			case 4 : {
				switch (first->_coordy) {
					case 0 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]-_winHeight+100) > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 1 : {
						if( (first->_position[1]-_winHeight+100) > second->_position[1] ) {
							_update = true;
						}
						break;
					}
					case 2 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]-_winHeight+100) > second->_position[1] ) ){
							_update = true;
						}
						break;
					}
					case 3 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > (second->_position[0]) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 5 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > (second->_position[0])) ) {
							_update = true;
						}
						break;
					}
				}
				break;
			}
			case 5 : {
				switch (first->_coordy) {
					case 0 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 1 : {
						if( (first->_position[1]) < second->_position[1]-_winHeight+100 ) {
							_update = true;
						}
						break;
					}
					case 2 : {
						if( (first->_position[1]) < second->_position[1]-_winHeight+100 ) {
							_update = true;
						}
						break;
					}
					case 3 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > (second->_position[0]) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 4 : {
						if( (first->_position[0] < (second->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
					case 5 : {
						if( (first->_position[0]-_winWidth+abs(second->_position[1]-first->_position[1])/1.2 > (second->_position[0]) ) || ( (first->_position[1]) < second->_position[1]-_winHeight+100 ) ){
							_update = true;
						}
						break;
					}
				}
				break;
			}
		}
		
		if(_update) {
			first->_velocity = 0;
			first->_points++;
			first->_position[0] = second->_coordx*_piecesize+(_piecesize/2)-(_piecesize/6);
			first->_position[1] = second->_coordy*_piecesize+(_piecesize/2);
			second->_velocity = 0;
			second->_points--;
			second->_position[0] = second->_coordx*_piecesize+(_piecesize/2)+(_piecesize/6);
			second->_position[1] = second->_coordy*_piecesize+(_piecesize/2);
		}	
		
	}

	void MyController::draw() {
		//glColor3d(0,0,0);
		//glLineWidth(1);
		//glBegin(GL_LINE_LOOP);
			//glVertex3f(_car1bottomleft[0], _car1bottomleft[1], _car1->height);
			//glVertex3f(_car1bottomright[0], _car1bottomright[1], _car1->height);
			//glVertex3f(_car1topright[0], _car1topright[1], _car1->height);
			//glVertex3f(_car1topleft[0], _car1topleft[1], _car1->height);
		//glEnd();
		
		//glBegin(GL_LINE_LOOP);
			//glVertex3f(_car2bottomleft[0], _car2bottomleft[1], _car2->height);
			//glVertex3f(_car2bottomright[0], _car2bottomright[1], _car2->height);
			//glVertex3f(_car2topright[0], _car2topright[1], _car2->height);
			//glVertex3f(_car2topleft[0], _car2topleft[1], _car2->height);
		//glEnd();		
		
	}

	
	// 1st player - USED TO BE 2ND!!!
	void MyController::onSpecialKeyPressed(int key) {
		if (key == GLUT_KEY_UP) {
			_car1->setUpKeyReleased(false);
			_car1->setUpKeyPressed(true);
		}
		if (key == GLUT_KEY_LEFT) {
			_car1->setLeftKeyReleased(false);
			_car1->setRightKeyReleased(false);
			_car1->setLeftKeyPressed(true);
		}
		if (key == GLUT_KEY_RIGHT) {
			_car1->setRightKeyReleased(false);
			_car1->setLeftKeyReleased(false);
			_car1->setRightKeyPressed(true);
		}
		if (key == GLUT_KEY_DOWN) {
			_car1->setDownKeyReleased(false);
			_car1->setDownKeyPressed(true);
		}
	}


	void MyController::onSpecialKeyReleased(int key) {
        if (key == GLUT_KEY_UP) {
			_car1->setUpKeyPressed(false);
			_car1->setUpKeyReleased(true);
		}
		if (key == GLUT_KEY_LEFT) {
			_car1->setLeftKeyPressed(false);
			_car1->setLeftKeyReleased(true);
		}
		if (key == GLUT_KEY_RIGHT) {
			_car1->setRightKeyPressed(false);
			_car1->setRightKeyReleased(true);
		}
		if (key == GLUT_KEY_DOWN) {
			_car1->setDownKeyPressed(false);
			_car1->setDownKeyReleased(true);
		} 
	}
	
	
	// 2nd player - USED TO BE 1ST!!!	&	Esc
	void MyController::onKeyPressed(unsigned char key) {
		if (key == 119) {
			_car2->setUpKeyReleased(false);
			_car2->setUpKeyPressed(true);
		}
		if (key == 97) {
			_car2->setLeftKeyReleased(false);
			_car2->setRightKeyReleased(false);
			_car2->setLeftKeyPressed(true);
		}
		if (key == 100) {
			_car2->setRightKeyReleased(false);
			_car2->setLeftKeyReleased(false);
			_car2->setRightKeyPressed(true);
		}
		if (key == 115) {
			_car2->setDownKeyReleased(false);
			_car2->setDownKeyPressed(true);
		}
		
		if (key == 27) {
			cg::Manager::instance()->shutdownApp();
        }
	}


	void MyController::onKeyReleased(unsigned char key) {
        if (key == 119) {
			_car2->setUpKeyPressed(false);
			_car2->setUpKeyReleased(true);
		}
		if (key == 97) {
			_car2->setLeftKeyPressed(false);
			_car2->setLeftKeyReleased(true);
		}
		if (key == 100) {
			_car2->setRightKeyPressed(false);
			_car2->setRightKeyReleased(true);
		}
		if (key == 115) {
			_car2->setDownKeyPressed(false);
			_car2->setDownKeyReleased(true);
		} 
	}

}
