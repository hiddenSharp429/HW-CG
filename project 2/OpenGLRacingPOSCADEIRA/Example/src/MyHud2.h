#ifndef MY_HUD2_H
#define MY_HUD2_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyCar.h"

namespace tutorial {

	class MyHud2 : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;
		
		std::string _elapsedTimeText, _danoText, _velocityText, _pointsText;
		std::string _danoMessage, _elapsedTimeMessage, _velocityMessage, _bonusMessage, _pointsMessage;
		std::string _danoMessage2, _elapsedTimeMessage2, _velocityMessage2, _bonusMessage2, _pointsMessage2;
		

	public:
		MyHud2(std::string id);
		~MyHud2();
		MyCar* _car1;
		MyCar* _car2;
		void init();
		void update(unsigned long elapsed_millis);
		void drawOverlay();
		void onReshape(int width, int height);

	};

	
}
#endif
