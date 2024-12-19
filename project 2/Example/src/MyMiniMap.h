#ifndef MY_MINI_MAP_H
#define MY_MINI_MAP_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyTrackPiece.h"
#include "MyTrackPiece2.h"
#include "MyObstacle.h"
#include "MyObstacle2.h"
#include "MyCar.h"
#include "MyBonus.h"
#include "MyBonus2.h"
#include "MyCamera.h"

namespace tutorial {

	class MyMiniMap : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;
		
		std::string _elapsedTimeText, _danoText, _velocityText, _bonusText, _bonusMessage, _bonusMessage2;
		std::string _danoMessage, _elapsedTimeMessage, _velocityMessage;


	public:
		MyMiniMap(std::string id);
		~MyMiniMap();
		MyCamera* _cam;
		MyCar* _car1;
		MyCar* _car2;
		MyTrackPiece* _trackpiece;
		MyTrackPiece2* _trackpiece2;
		MyObstacle* _ballObstacle1;
		MyObstacle* _ballObstacle2;
		MyObstacle* _ballObstacle3;
		MyObstacle2* _movingObstacle1;
		MyBonus* _speedBonus1;
		MyBonus2* _damageBonus1;
		void init();
		void update(unsigned long elapsed_millis);
		void drawOverlay();
		void onReshape(int width, int height);

	};

	
}
#endif
