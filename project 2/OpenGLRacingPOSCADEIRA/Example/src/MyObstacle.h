#ifndef MY_OBSTACLE_H
#define MY_OBSTACLE_H

#include <string>
#include "cg/cg.h"
#include "MyCar.h"

namespace tutorial {

	class MyObstacle : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		int _transx, _transy;
		MyCar* _car1;
		MyCar* _car2;	
	
		
	public:
		MyObstacle(std::string id, double transx, double transy);
		~MyObstacle();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		bool isCollision(cg::Vector3d car_position, double car_length);

		
	};

	
}
#endif
