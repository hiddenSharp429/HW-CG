#include "MyHud2.h"

namespace tutorial {
	
	
	MyHud2::MyHud2(std::string id) : cg::Entity(id) {
	}
	MyHud2::~MyHud2() {
	}
	
	void MyHud2::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_elapsedTimeText = "Time: ";
		_danoText = "Damage: ";
		_velocityText = "Speed: ";
		_pointsText = "Points: ";

		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");
		
	}

	void MyHud2::update(unsigned long elapsed_millis) {
        
		std::stringstream danoout;
		danoout << _car1->_dano;
		_danoMessage = danoout.str();

		std::stringstream danoout2;
		danoout2 << _car2->_dano;
		_danoMessage2 = danoout2.str();
		
		
		std::stringstream velout;
		velout << (int)_car1->_velocity;
		_velocityMessage = velout.str();
		
		std::stringstream velout2;
		velout2 << (int)_car2->_velocity;
		_velocityMessage2 = velout2.str();
		
		
		std::stringstream timeout;
		timeout << _car1->_elapsedTime;
		_elapsedTimeMessage = timeout.str();
		
		std::stringstream timeout2;
		timeout2 << _car2->_elapsedTime;
		_elapsedTimeMessage2 = timeout2.str();
		
		
		std::stringstream pointsout;
		pointsout << _car1->_points;
		_pointsMessage = pointsout.str();

		std::stringstream pointsout2;
		pointsout2 << _car2->_points;
		_pointsMessage2 = pointsout2.str();
	}

	void MyHud2::drawOverlay() {

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0,_winWidth,0,_winHeight,0,-100);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		
		float specular[] = { .0, .0, .0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		float fDiffuse[] = {0.f, 0.f, 0.f, .25f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse);
				
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0.0,0.0,0.0, .25);
		glTranslated(80,60,0);		// Big box to make the laggy text fit
		glScaled(160,120,1);
//		glTranslated(50,40,0);		// Small box as backup if the text lags
//		glScaled(100,80,1);
		glutSolidCube(1);
		glDisable(GL_BLEND);
		glPopMatrix();
		
		// 2nd player hud
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0.0,0.0,0.0, .25);
		glTranslated(_winWidth-80,60,0);		// Big box 2 to make the laggy text fit
		glScaled(160,120,1);
//		glTranslated(_winWidth-50,40,0);		// Small box 2 as backup if the text lags
//		glScaled(100,80,1);
		glutSolidCube(1);
		glDisable(GL_BLEND);
		glPopMatrix();
		
		glDisable(GL_LIGHTING);
		glColor3d(0.8,0.8,0.0);
		
		// Player 1 messages
		glRasterPos2i( 10, 15);
		for (std::size_t i = 0; i < _elapsedTimeText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _elapsedTimeText[i]);
		glRasterPos2i( 100, 15);
//		glRasterPos2i( 20, 15);
		for (std::size_t i = 0; i < _elapsedTimeMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _elapsedTimeMessage[i]);
		
		glRasterPos2i( 10, 35);
		for (std::size_t i = 0; i < _danoText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoText[i]);
		glRasterPos2i( 100, 35);
//		glRasterPos2i( 20, 35);
		for (std::size_t i = 0; i < _danoMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoMessage[i]);
		
		glRasterPos2i( 10, 55);
		for (std::size_t i = 0; i < _velocityText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _velocityText[i]);
		glRasterPos2i( 100, 55);
//		glRasterPos2i( 20, 55);
		for (std::size_t i = 0; i < _velocityMessage.size(); i++)
            glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _velocityMessage[i]);

		glRasterPos2i(10, 75);
		for (std::size_t i = 0; i < _pointsText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _pointsText[i]);
		glRasterPos2i(100, 75);
//		glRasterPos2i( 20, 75);
		for (std::size_t i = 0; i < _pointsMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _pointsMessage[i]);
			
		glRasterPos2i( 10, 95);
//		glRasterPos2i( 20, 95);
		if(_car1->_speedBonus)
			_bonusMessage = "2x vel";
		else
			_bonusMessage = "---";
		for (std::size_t i = 0; i < _bonusMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
			
		
		glRasterPos2i( 75, 95);
//		glRasterPos2i( 20, 95);
		if(_car1->_damageBonus)
			_bonusMessage = ".5 dmg";
		else
			_bonusMessage = "---";
		for (std::size_t i = 0; i < _bonusMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
            

		glColor3d(1.0,1.0,1.0);
		if(_car1->_dano == 10) {
			_danoMessage = "Congratulations player 1! You wrecked your car!";
			glRasterPos2i(120, _winHeight-20);
			for (std::size_t i = 0; i < _danoMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoMessage[i]);
		}
		
		glColor3d(0.8,0.8,0.0);
		
		// Player 2 messages
		glRasterPos2i( _winWidth-160+10, 15);
		for (std::size_t i = 0; i < _elapsedTimeText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _elapsedTimeText[i]);
		glRasterPos2i( _winWidth-160+100, 15);
//		glRasterPos2i( _winWidth-50+20, 15);
		for (std::size_t i = 0; i < _elapsedTimeMessage2.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _elapsedTimeMessage2[i]);
		
		glRasterPos2i( _winWidth-160+10, 35);
		for (std::size_t i = 0; i < _danoText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoText[i]);
		glRasterPos2i( _winWidth-160+100, 35);
//		glRasterPos2i( _winWidth-50+20, 35);
		for (std::size_t i = 0; i < _danoMessage2.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoMessage2[i]);
		
		glRasterPos2i( _winWidth-160+10, 55);
		for (std::size_t i = 0; i < _velocityText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _velocityText[i]);
		glRasterPos2i( _winWidth-160+100, 55);
//		glRasterPos2i( _winWidth-50+20, 55);
		for (std::size_t i = 0; i < _velocityMessage2.size(); i++)
            glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _velocityMessage2[i]);

		glRasterPos2i( _winWidth-160+10, 75);
		for (std::size_t i = 0; i < _pointsText.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _pointsText[i]);
		glRasterPos2i( _winWidth-160+100, 75);
//		glRasterPos2i( _winWidth-50+20, 75);
		for (std::size_t i = 0; i < _pointsMessage2.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _pointsMessage2[i]);
			
		glRasterPos2i( _winWidth-160+10, 95);
//		glRasterPos2i( _winWidth-50+20, 95);
		if(_car2->_speedBonus)
			_bonusMessage2 = "2x vel";
		else
			_bonusMessage2 = "---";
		for (std::size_t i = 0; i < _bonusMessage2.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage2[i]);
			
		glRasterPos2i( _winWidth-160+75, 95);
//		glRasterPos2i( _winWidth-50+20, 95);
		if(_car2->_damageBonus)
			_bonusMessage2 = ".5 dmg";
		else
			_bonusMessage2 = "---";
		for (std::size_t i = 0; i < _bonusMessage2.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage2[i]);



		glColor3d(1.0,1.0,1.0);
		if(_car2->_dano == 10) {
			_danoMessage = "Congratulations player 2! You wrecked your car!";
			glRasterPos2i(120, _winHeight-40);
			for (std::size_t i = 0; i < _danoMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoMessage[i]);
		}
		
		if( (_car1->_speedBonus) && (_car1->_speedBonusTime < 2) ) {
			_bonusMessage = "Player 1 speed bonus activated!";
			glRasterPos2i(160, _winHeight/2+40);
			for (std::size_t i = 0; i < _bonusMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
		}

		if( (_car2->_speedBonus) && (_car2->_speedBonusTime < 2) ) {
			_bonusMessage = "Player 2 speed bonus activated!";
			glRasterPos2i(160, _winHeight/2+20);
			for (std::size_t i = 0; i < _bonusMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
		}
		
		if( (_car1->_damageBonus) && (_car1->_damageBonusTime < 2) ) {
			_bonusMessage2 = "Player 1 damage bonus activated!";
			glRasterPos2i(160, _winHeight/2);
			for (std::size_t i = 0; i < _bonusMessage2.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage2[i]);
		}

		if( (_car2->_damageBonus) && (_car2->_damageBonusTime < 2) ) {
			_bonusMessage2 = "Player 2 damage bonus activated!";
			glRasterPos2i(160, _winHeight/2-20);
			for (std::size_t i = 0; i < _bonusMessage2.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage2[i]);
		}
		
		glEnable(GL_LIGHTING);
	}
	
	void MyHud2::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
