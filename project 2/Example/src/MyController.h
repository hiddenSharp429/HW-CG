#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"
#include "MyCar.h"
#include "MyObstacle.h"
#include "MyObstacle2.h"
#include "MyTrack.h"
#include "MyCamera.h"

namespace tutorial {

	class MyController : public cg::Entity,
		public cg::IKeyboardEventListener,
		public cg::IDrawListener,
		public cg::IUpdateListener
	{
	private:
		MyCar* _car1;
		MyCar* _car2;
		MyCamera* _cam;

		double _winWidth, _winHeight, _car1width, _car1length, _car2width, _car2length, _car1angle, _car2angle;
		cg::Vector2d _car1bottomleft, _car1bottomright, _car1topright, _car1topleft, _car2bottomleft, _car2bottomright, _car2topright, _car2topleft;

	public:
		MyObstacle* _ballObstacle1;
		MyObstacle* _ballObstacle2;
		MyObstacle* _ballObstacle3;
		MyObstacle2* _movingObstacle1;
		MyController();
		~MyController();
		void updatePoints(MyCar* first, MyCar* second);
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
		void update(unsigned long elapsed_millis);
		void draw();
		
	};
}

#endif
