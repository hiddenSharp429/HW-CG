#ifndef MY_HUD_H
#define MY_HUD_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyCar.h"

namespace tutorial {

	class MyHud : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;
		
		std::string _elapsedTimeText, _danoText, _velocityText, _bonusText, _bonusMessage, _bonusMessage2;
		std::string _danoMessage, _elapsedTimeMessage, _velocityMessage;


	public:
		MyHud(std::string id);
		~MyHud();
		MyCar* _car1;
		void init();
		void update(unsigned long elapsed_millis);
		void drawOverlay();
		void onReshape(int width, int height);

	};

	
}
#endif
