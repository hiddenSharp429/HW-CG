#ifndef MY_OBSTACLE2_H
#define MY_OBSTACLE2_H

#include <string>
#include "cg/cg.h"
#include "MyCar.h"

namespace tutorial {

	class MyObstacle2 : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		bool _sentido;					// true se pos, false se neg (eixo dos xx)
		double _posx, _posy;
		MyCar* _car1;
		MyCar* _car2;
		
	public:
		MyObstacle2(std::string id, double posx, double posy);
		~MyObstacle2();
		double _positionx;
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		bool isCollision(cg::Vector3d car_position, double car_length);

		
	};

	
}
#endif
