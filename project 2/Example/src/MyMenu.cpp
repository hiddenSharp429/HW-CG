#include "MyMenu.h"

namespace tutorial {
	
	
	MyMenu::MyMenu(std::string id) : cg::Entity(id) {
	}
	MyMenu::~MyMenu() {
	}
	
	void MyMenu::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;


		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");
		
		_hud1 = (MyHud*)cg::Registry::instance()->get("Hud");
		_hud2 = (MyHud2*)cg::Registry::instance()->get("Hud2");
		
		_cam = (MyCamera*)cg::Registry::instance()->get("Camera");
		_controller = (MyController*)cg::Registry::instance()->get("Controller");
		_minimap = (MyMiniMap*)cg::Registry::instance()->get("MiniMap");
		
	}

	void MyMenu::update(unsigned long elapsed_millis) {
		
		_car1->state.disable();
		_car2->state.disable();
		_hud1->state.disable();
		_hud2->state.disable();
		_minimap->state.disable();
		_controller->state.disable();
	}

	void MyMenu::drawOverlay() {

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0,_winWidth,0,_winHeight,0,-100);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float specular[] = { .0, .0, .0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		float fDiffuse[] = {0.8f, 0.8f, 0.8f, .5f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse);

		glColor4d(0.0,0.0,0.0, .5);
		glTranslated(_winWidth/2,_winHeight/2,0);		// Big box to make the laggy text fit
		glScaled(_winWidth,_winHeight,1);
		glutSolidCube(1);
		glDisable(GL_BLEND);
		glPopMatrix();
		

		glDisable(GL_LIGHTING);
		glColor3d(0.8,0.8,0.0);
		
		std::string _menumsg = "Press 1 for 1 player               Press 2 for 2 players";
		glRasterPos2i( _winWidth/2-_menumsg.size()*9/2, _winHeight/2);	// *9 because every letter uses 9 pixels in the x-direction
		for (std::size_t i = 0; i < _menumsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _menumsg[i]);
		
		
		// Identificação
		std::string _bymsg = "By:";
		std::string _rosamsg = "Rosa Bernardino";
		std::string _pedromsg = "Pedro Natario";
		std::string _atmsg = "For:";
		std::string _cgmsg = "Computacao Grafica 2010-11";
		std::string _istmsg = "Instituto Superior Tecnico";
		glRasterPos2i( 5, 45);
		for (std::size_t i = 0; i < _bymsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _bymsg[i]);
		glRasterPos2i( 5, 25);
		for (std::size_t i = 0; i < _pedromsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _pedromsg[i]);
		//glRasterPos2i( 5, 5);
		//for (std::size_t i = 0; i < _rosamsg.size(); i++)
			//glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _rosamsg[i]);
			
		glRasterPos2i( _winWidth-_cgmsg.size()*9-5, 45);
		for (std::size_t i = 0; i < _atmsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _atmsg[i]);
		glRasterPos2i( _winWidth-_cgmsg.size()*9-5, 25);
		for (std::size_t i = 0; i < _cgmsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _cgmsg[i]);
		glRasterPos2i( _winWidth-_istmsg.size()*9-5, 5);
		for (std::size_t i = 0; i < _istmsg.size(); i++)
			glutBitmapCharacter( GLUT_BITMAP_9_BY_15, _istmsg[i]);
		

		glEnable(GL_LIGHTING);
	}
	
	void MyMenu::onKeyPressed(unsigned char key) {
		if (key == 49) {					// Tecla 1
			_car1->state.enable();
			_hud1->state.enable();
			_cam->_numplayers = 1;
			_minimap->state.enable();
			_controller->state.enable();
			
			
			
			state.disable();
		}
		if (key == 50) {					// Tecla 2
			_car1->state.enable();
			_car2->state.enable();
			_hud2->state.enable();
			_cam->_numplayers = 2;
			_minimap->state.enable();
			_controller->state.enable();
			
			state.disable();
		}
	}


	void MyMenu::onKeyReleased(unsigned char key) {
	}	

	void MyMenu::onSpecialKeyPressed(int key){
	}
	void MyMenu::onSpecialKeyReleased(int key){
	}

	
	void MyMenu::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
