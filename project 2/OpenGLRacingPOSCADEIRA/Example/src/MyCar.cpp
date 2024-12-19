#include "MyCar.h"

namespace tutorial {

	MyCar::MyCar(std::string id) : cg::Entity(id) {
	}
	
	MyCar::MyCar(double posx, double posy, std::string id, int cor) : cg::Entity(id) {
		_posx = posx;
		_posy = posy;
		_cor = cor;
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
		height = cg::Properties::instance()->getDouble("CAR_HEIGHT");	// altura do carro (eixo zz) - profundidade(não perceptível a 2D)
		_initmaxvel = cg::Properties::instance()->getDouble("CAR_INITIAL_MAX_VELOCITY");
		_use3dmodels = cg::Properties::instance()->getInt("USE_3D_MODELS_FOR_VEHICLES");
		_piecesize = cg::Properties::instance()->getDouble("TRACKPIECE_SIZE");
		
		// Creates car
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_position[0] = _posx;		// Car creation x coordinate
		_position[1] = _posy;		// Car creation y coordinate
		_size = cg::Vector3d(width, length, height);
		_color = cg::Vector3d(randomBetween(0.1,0.9),randomBetween(0.1,0.9),randomBetween(0.1,0.9));
		_angle = 0;
		_collisionAngle = 0;
		_collisionVelocity = 0;
		_acceleration = 0;
		_velocity = 0;
		_maxvel = _initmaxvel;
		_dano = 0;
		_points = 0;
		_elapsedTime = 0;
		_colliding = false;
		_speedBonusTime = 0;
		_damageBonusTime = 0;
		_speedBonus = false;
		_damageBonus = false;
		_updateVel = false;		// False -> car is on the road, normal velocity; True -> car is on the grass, slower velocity.


		// Links for collisions
		_speedBonus1 = (MyBonus*)cg::Registry::instance()->get("SpeedBonus1");
		_damageBonus1 = (MyBonus2*)cg::Registry::instance()->get("DamageBonus1");
		
		
		_upKeyPressed = false;
		_leftKeyPressed = false;
		_rightKeyPressed = false;
		_downKeyPressed = false;
		_upKeyReleased = false;
		_leftKeyReleased = false;
		_rightKeyReleased = false;
		_downKeyReleased = false;
		
		
		
		texture[0] = LoadTextureRAW( "textures/particle_mask.raw",256,256);	//load our texture
		texture[1] = LoadTextureRAW( "textures/particle.raw",256,256);		//load our texture
		



		
		model=glmReadOBJ("textures/porsche.obj");
		
		int i;
		for (i = 1; i < ParticleCount; i++) {
			Particle[i].Xpos = _position[0];
			Particle[i].Ypos = _position[1]-length/2;
			Particle[i].Zpos = 20;
			Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
			Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
			Particle[i].Red = .8;
			Particle[i].Green = .8;
			Particle[i].Blue = .8;
			Particle[i].Scalez = 2.5;
			Particle[i].Direction = 0;
			Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
			Particle[i].Deceleration = 0.0025;
		}
	
	}
	
	void MyCar::update(unsigned long elapsed_millis) {

		double elapsed_seconds = elapsed_millis / 1000.0;
		

		if(_velocity == 0)
			_acceleration = 0;
		
		// "Virtual" Pitstop
//		cg::Vector2d pitstop_bottomleft, pitstop_topright, car_bottomleft, car_topright;	
//		pitstop_bottomleft[0] = 0;
//		pitstop_bottomleft[1] = 600;
//		pitstop_topright[0] = 300;
//		pitstop_topright[1] = 1200;
//		car_bottomleft[0] = _position[0] - length / 2.0;
//		car_bottomleft[1] = _position[1] - length / 2.0;
//		car_topright[0] = _position[0] + length / 2.0;
//		car_topright[1] = _position[1] + length / 2.0;
//		if( cg::Util::instance()->isAABBoxCollision(pitstop_bottomleft,pitstop_topright,car_bottomleft,car_topright)  )
//			_dano = 0;
		


		if( _speedBonus1->isCollision(_position, length) && _speedBonus1->state.isEnabled() ) {
			
			_speedBonus = true;
			_maxvel *=2;
			_speedBonus1->state.disable();
			
		}
		
		if( _damageBonus1->isCollision(_position, length) && _damageBonus1->state.isEnabled() ) {
			
			_damageBonus = true;
			_damageBonus1->state.disable();
			
		}
		

		
		if (isUpKeyPressed()) {
//			setDownKeyReleased(false);
			//_collisionAngle = 0;
			if(_maxvel > 0) {
				if(_acceleration <= 100)
					_acceleration+=5;
				if(_velocity <= 0)
					_velocity += 2*_acceleration * elapsed_seconds;
				if(_velocity <= _maxvel)
					_velocity += _acceleration * elapsed_seconds;
				else
					_velocity -= 10*_acceleration * elapsed_seconds;
			}

		}
		
		if (isUpKeyReleased()) {
			if(_velocity <= 0)	{	// The effect of releasing the up key (deacceleration) is no longer needed since the car has stopped
				setUpKeyReleased(false);	
				//_collisionAngle = 0;
				
			}
			if(_acceleration <= 100)
				_acceleration++;

			if(_velocity > 0) {
				_velocity += -_acceleration * elapsed_seconds;
				if(_velocity < 0)
					_velocity = 0;
			}
		}
		
		
		if (isLeftKeyPressed()) {
			if(_velocity > 0) {
				if(_dano < 5)
					_angle+=3;
				else
					_angle++;
			}
			if(_velocity < 0) {
				if(_dano < 5)
					_angle-=3;
				else
					_angle--;
			}
		}
		if (isRightKeyPressed()) {
			if(_velocity > 0) {
				if(_dano < 5)
					_angle-=3;
				else
					_angle--;
			}
			if(_velocity < 0) {
				if(_dano < 5)
					_angle+=3;
				else
					_angle++;
			}
		}		

		// ang 0	= car facing "north" (positive-yy)		I
		// ang 90	= car facing "west" (negative-xx)		THINK
		// ang 180	= car facing "south" (negative-yy)		SO
		// ang 270	= car facing "east" (positive-xx)		...
		if( abs(_angle) == 360 )
			_angle = 0;


		if (isDownKeyPressed()) {
//			setUpKeyReleased(false);
			//_collisionAngle = 0;
			if(_maxvel > 0 ) {
				if(_acceleration <= 50)
					_acceleration++;
				if(_velocity >= 0)
					_velocity += -_acceleration * elapsed_seconds;
				if(_velocity >= -50)
					_velocity += -_acceleration * elapsed_seconds;
			}

		}
		
		if (isDownKeyReleased()) {
			if(_velocity >= 0)	{	// The effect of releasing the down key (deacceleration of reverse) is no longer needed since the car has stopped
				setDownKeyReleased(false);
				//_collisionAngle = 0;
			}
			if(_acceleration <= 500)
				_acceleration++;
			if(_velocity < 0) {
				_velocity += _acceleration * elapsed_seconds;
				if(_velocity > 0)
					_velocity = 0;
			}

		}
		
		
		

		
		
		
		// Find out on which track piece the car is
		if(_position[0] > 0)
			_coordx = _position[0]/_piecesize;
		if(_position[0] < 0)
			_coordx = _position[0]/_piecesize-1;
		if(_position[1] > 0)
			_coordy = _position[1]/_piecesize;
		if(_position[1] < 0)
			_coordy = _position[1]/_piecesize-1;


		/************************************
		 *
		 * _dano represents the number of equal "parcels"(out of 10) of _initmaxvel to remove from the car's actual _maxvel.
		 * Eg: if the initmaxvel is 400, each parcel will be 40,
		 * and, if the _dano value is 3, it means that 30%(3/10) of the car is damaged,
		 * so 3 parcels of 40(3*40) will be removed from the car's _initmaxvel, making the actual _maxvel 280 (70% of the initial value)
		 * 
		 ************************************/
		if(_updateVel)
			if(_maxvel < 50)
				_maxvel = 15;
			else
				_maxvel = 50;
		else
			if(_speedBonus)
				_maxvel = _initmaxvel*2 - _dano * (_initmaxvel*2/10);
			else
				_maxvel = _initmaxvel - _dano * (_initmaxvel/10);
								
								
		_position[0] += (_velocity) * elapsed_seconds*sin(((-_angle)*3.14)/180);
		_position[1] += (_velocity) * elapsed_seconds*cos(((-_angle)*3.14)/180);

		
		
		if (_collisionVelocity > 0)
		{
			_position[0] += (_collisionVelocity) * elapsed_seconds*sin(((-_collisionAngle)*3.14)/180);
			_position[1] += (_collisionVelocity) * elapsed_seconds*cos(((-_collisionAngle)*3.14)/180);
			_collisionVelocity*=0.95;
			if (_collisionVelocity < 10) _collisionVelocity = 0; 
		}

		if (_collisionVelocity < 0)
		{
			_position[0] += (_collisionVelocity) * elapsed_seconds*sin(((-_collisionAngle)*3.14)/180);
			_position[1] += (_collisionVelocity) * elapsed_seconds*cos(((-_collisionAngle)*3.14)/180);
			_collisionVelocity*=0.95;
			if (_collisionVelocity > -10) _collisionVelocity = 0; 
		}
		
	
		if(_dano > 10)
			_dano = 10;

		if(_dano < 10)
			_elapsedTime += elapsed_seconds;
		
		if(_speedBonus)
			if(_speedBonusTime < 10)
				_speedBonusTime += elapsed_seconds;
			else {
				_speedBonusTime = 0;
				_speedBonus = false;
				_speedBonus1->_rand = _speedBonus1->randomBetween(1,5);
				_speedBonus1->state.enable();
				
			}
		else
			_speedBonusTime = 0;
			
		if(_damageBonus)
			if(_damageBonusTime < 10)
				_damageBonusTime += elapsed_seconds;
			else {
				_damageBonusTime = 0;
				_damageBonus = false;
				_damageBonus1->_rand = _damageBonus1->randomBetween(1,5);
				_damageBonus1->state.enable();
				
			}
		else
			_damageBonusTime = 0;

		
	
/*		// Appear on the opposite side of the window
		if(_position[1] > _winHeight/2)
			_position[1] = -_winHeight/2;
		if(_position[1] < -_winHeight/2)
			_position[1] = _winHeight/2;
		if(_position[0] > _winWidth/2)
			_position[0] = -_winWidth/2;
		if(_position[0] < -_winWidth/2)
			_position[0] = _winWidth/2;
*/



		// If car gets to the window limits, respawn at the center
/*		if((_position[0] < -_winWidth/2) || (_position[0] > _winWidth/2) || (_position[1] < -_winHeight/2) || (_position[1] > _winHeight/2)) { 
			_position[0] = 0.0;
			_position[1] = 0.0;
			_velocity[0] = 0.0;
			_velocity[1] = 0.0;

		}
*/

				
		if(_dano > 5) {
			int i;
			for (i = 1; i < ParticleCount; i++) {

				Particle[i].Deceleration = Particle[i].Deceleration + 0.0025;

				Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
				Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;

				Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);


				cg::Vector2d particle_bottomleft, particle_topright;	
				particle_bottomleft[0] = Particle[i].Xpos-Particle[i].Scalez/2;
				particle_bottomleft[1] = Particle[i].Ypos-Particle[i].Scalez/2;
				particle_topright[0] = Particle[i].Xpos+Particle[i].Scalez/2;
				particle_topright[1] = Particle[i].Ypos+Particle[i].Scalez/2;
				
				if( ((_velocity > 0) && (abs(_angle) < 90)) || ((_velocity < 0) && (abs(_angle) > 90)) ) {
					Particle[i].Ypos = Particle[i].Ypos - Particle[i].Acceleration;
					if( (Particle[i].Ypos < _position[1]-length*2) || (Particle[i].Xpos < _position[0]-width*2)
					||	(Particle[i].Ypos > _position[1]+length*2) || (Particle[i].Xpos > _position[0]+width*2) ) {
						
						Particle[i].Xpos = _position[0];
						Particle[i].Ypos = _position[1]-length/2;
						Particle[i].Zpos = 20;

					}
				}
				else {
					Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration;
					if( (Particle[i].Ypos < _position[1]-length*2) || (Particle[i].Xpos < _position[0]-width*2)
					||	(Particle[i].Ypos > _position[1]+length*2) || (Particle[i].Xpos > _position[0]+width*2) ) {
						
						Particle[i].Xpos = _position[0];
						Particle[i].Ypos = _position[1]-length/2;
						Particle[i].Zpos = 20;

					}
				}
				

			}
		}

	}	// UPDATE
	
	
	
	void MyCar::draw() {

		if(_dano > 5) {
			int i;
			for (i = 1; i < ParticleCount; i++)	{
				glPushMatrix();
				
				glColor3f (Particle[i].Red, Particle[i].Green, Particle[i].Blue);
				
				glTranslatef (Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
				glRotatef (Particle[i].Direction - 90, 0, 0, 1);
			   
				glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);
			   
				glDisable (GL_DEPTH_TEST);
				glEnable (GL_BLEND);
					
				glBlendFunc (GL_DST_COLOR, GL_ZERO);
				glBindTexture (GL_TEXTURE_2D, texture[0]);

				glBegin (GL_QUADS);
				glTexCoord2d (0, 0);
				glVertex3f (-1, -1, 0);
				glTexCoord2d (1, 0);
				glVertex3f (1, -1, 0);
				glTexCoord2d (1, 1);
				glVertex3f (1, 1, 0);
				glTexCoord2d (0, 1);
				glVertex3f (-1, 1, 0);
				glEnd();
				
				glBlendFunc (GL_ONE, GL_ONE);
				glBindTexture (GL_TEXTURE_2D, texture[1]);
				
				glBegin (GL_QUADS);
				glTexCoord2d (0, 0);
				glVertex3f (-1, -1, 0);
				glTexCoord2d (1, 0);
				glVertex3f (1, -1, 0);
				glTexCoord2d (1, 1);
				glVertex3f (1, 1, 0);
				glTexCoord2d (0, 1);
				glVertex3f (-1, 1, 0);
				glEnd();
					
				glEnable(GL_DEPTH_TEST);
				glDisable (GL_BLEND);
				glPopMatrix();

			}
		}
	
		

		static GLfloat n[6][3] = { {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
									{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
									{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
		static GLint faces[6][4] = { {0, 1, 2, 3}, {3, 2, 6, 7},
									{7, 6, 5, 4}, {4, 5, 1, 0},
									{5, 6, 2, 1}, {7, 4, 0, 3} };
		GLfloat v[8][3];
		GLint iwtf;
		
		if(_minimapMode) {
			v[0][0] = v[1][0] = v[2][0] = v[3][0] = -(width*4) / 2;
			v[4][0] = v[5][0] = v[6][0] = v[7][0] = (width*4) / 2;
			v[0][1] = v[1][1] = v[4][1] = v[5][1] = -(length*4) / 2;
			v[2][1] = v[3][1] = v[6][1] = v[7][1] = (length*4) / 2;
			v[0][2] = v[3][2] = v[4][2] = v[7][2] = -height / 2;
			v[1][2] = v[2][2] = v[5][2] = v[6][2] = height / 2;
		}
		else {
			v[0][0] = v[1][0] = v[2][0] = v[3][0] = -width / 2;
			v[4][0] = v[5][0] = v[6][0] = v[7][0] = width / 2;
			v[0][1] = v[1][1] = v[4][1] = v[5][1] = -length / 2;
			v[2][1] = v[3][1] = v[6][1] = v[7][1] = length / 2;
			v[0][2] = v[3][2] = v[4][2] = v[7][2] = -height / 2;
			v[1][2] = v[2][2] = v[5][2] = v[6][2] = height / 2;
		}
//		glColor3dv(_color.get());		// Random color
//		glColor3d(0.9,0,0);
//		glDisable(GL_COLOR_MATERIAL);

		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat mat_ambient_color[] = { 0.5, 0.0, 0.0, 1.0 };
		GLfloat mat_diffuse[] = { 0.5, 0.0, 0.0, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat no_shininess[] = { 0.0 };
		GLfloat low_shininess[] = { 5.0 };
		GLfloat high_shininess[] = { 50.0 };
		GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};


		if(_cor == 1 ) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		}
		else {
			float specular6[] = { .5, .0, .5, 1.0 };
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular6);
		}
		glPushMatrix();
		glTranslated(_position[0], _position[1], height/2);
		glRotated(_angle, 0, 0, 1);
		//glTranslated(-_position[0],-_position[1], 0);
		//glScaled(width,length,height);

/*************************************
 *
 * 3D model polygons
 * and
 * simple rectangular car
 *
 *************************************/		

		if(_use3dmodels) {
			glTranslated(0, 0, 12);
			glRotated(90, 1, 0, 0);
			glRotated(180, 0, 1, 0);
			glScaled(1,1,1);
			glmDraw(model,/*GLM_TEXTURE|*/GLM_MATERIAL|GLM_SMOOTH);
		}
		else {
			for (iwtf = 5; iwtf >= 0; iwtf--) {
				glBegin(GL_QUADS);
					glNormal3fv(&n[iwtf][0]);
					glVertex3fv(&v[faces[iwtf][0]][0]);
					glVertex3fv(&v[faces[iwtf][1]][0]);
					glVertex3fv(&v[faces[iwtf][2]][0]);
					glVertex3fv(&v[faces[iwtf][3]][0]);
				glEnd();
			}
		}
/************************************/
		
		float specular2[] = { .0, .0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
//		glBegin(GL_POLYGON);
//			glVertex3d(-width/2, -length/2, 0);
//			glVertex3d(width/2, -length/2, 0);
//			glVertex3d(width/2, length/2, 0);
//			glVertex3d(0, (length/2)+5, 0);
//			glVertex3d(-width/2, length/2, 0);
//		glEnd();
		glPopMatrix();

		//glEnable(GL_COLOR_MATERIAL);

		
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
	

	void MyCar::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
	
	
	
	//function to load the RAW file
	GLuint MyCar::LoadTextureRAW( const char * filename, int width, int height ) {
		
		GLuint texture;
		unsigned char * data;
		FILE * file;

		file = fopen( filename, "rb" );
		if ( file == NULL ) return 0;

		data = (unsigned char *)malloc( width * height * 3 );

		// Just to suppress warning: ignoring return value of ‘size_t fread(void*, size_t, size_t, FILE*)’, declared with attribute warn_unused_result
		size_t creturn;
		// read texture data
		creturn = fread( data, width * height * 3, 1, file );
		fclose( file );

		glGenTextures(1, &texture );            

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		free( data );

		return texture;
	}

	void MyCar::FreeTexture( GLuint texture )
	{
	  glDeleteTextures( 1, &texture );
	} 

}

