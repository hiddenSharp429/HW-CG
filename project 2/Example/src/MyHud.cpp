#include "MyHud.h"

namespace tutorial {
	
	
	MyHud::MyHud(std::string id) : cg::Entity(id) {
	}
	MyHud::~MyHud() {
	}
	
	void MyHud::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		_elapsedTimeText = "Time: ";
		_danoText = "Damage: ";
		_velocityText = "Speed: ";

		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		
	}

	void MyHud::update(unsigned long elapsed_millis) {
        
		std::stringstream danoout;
		danoout << _car1->_dano;
		_danoMessage = danoout.str();
		
		std::stringstream velout;
		velout << (int)_car1->_velocity;
		_velocityMessage = velout.str();
		
		std::stringstream timeout;
		timeout << _car1->_elapsedTime;
		_elapsedTimeMessage = timeout.str();
	}

	void MyHud::drawOverlay() {

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
		glTranslated(80,50,0);		// Big box to make the laggy text fit
		glScaled(160,100,1);
//		glTranslated(50,40,0);		// Small box as backup if the text lags
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

		glRasterPos2i( 10, 75);
//		glRasterPos2i( 20, 55);
		if(_car1->_speedBonus)
			_bonusMessage = "2x vel";
		else
			_bonusMessage = "---";
		for (std::size_t i = 0; i < _bonusMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
			
		
		glRasterPos2i( 75, 75);
//		glRasterPos2i( 20, 55);
		if(_car1->_damageBonus)
			_bonusMessage = ".5 dmg";
		else
			_bonusMessage = "---";
		for (std::size_t i = 0; i < _bonusMessage.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
            

		glColor3d(0.0,0.0,0.0);
		if(_car1->_dano == 10) {
			_danoMessage = "Congratulations! Player 1, you wrecked your car!";
			glRasterPos2i(120, _winHeight-20);
			for (std::size_t i = 0; i < _danoMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _danoMessage[i]);
		}
		
		
		if( (_car1->_speedBonus) && (_car1->_speedBonusTime < 2) ) {
			_bonusMessage = "Player 1 speed bonus activated!";
			glRasterPos2i(160, _winHeight/2+40);
			for (std::size_t i = 0; i < _bonusMessage.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage[i]);
		}
		
		if( (_car1->_damageBonus) && (_car1->_damageBonusTime < 2) ) {
			_bonusMessage2 = "Player 1 damage bonus activated!";
			glRasterPos2i(160, _winHeight/2);
			for (std::size_t i = 0; i < _bonusMessage2.size(); i++)
				glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bonusMessage2[i]);
		}
		
		
		glEnable(GL_LIGHTING);
	}
	
	
	void MyHud::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
	
}
