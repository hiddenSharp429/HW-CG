#ifndef MY_MENU_H
#define MY_MENU_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyCar.h"
#include "MyHud.h"
#include "MyHud2.h"
#include "MyCamera.h"
#include "MyController.h"
#include "MyMiniMap.h"

namespace tutorial {

	class MyMenu : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IUpdateListener,
		public cg::IKeyboardEventListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;
		
		

	public:
		MyMenu(std::string id);
		~MyMenu();
		MyCar* _car1;
		MyCar* _car2;
		MyHud* _hud1;
		MyHud2* _hud2;
		MyCamera* _cam;
		MyController* _controller;
		MyMiniMap* _minimap;
		void init();
		void update(unsigned long elapsed_millis);
		void drawOverlay();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
		void onSpecialKeyReleased(int key);
		void onReshape(int width, int height);

	};

	
}
#endif
