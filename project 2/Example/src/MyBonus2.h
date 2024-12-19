#ifndef MY_BONUS2_H
#define MY_BONUS2_H

#include <string>
#include "cg/cg.h"


namespace tutorial {

	class MyBonus2 : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		int _transx, _transy;
		
	public:
		MyBonus2(std::string id);
		~MyBonus2();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
        void onReshape(int width, int height);
		bool isCollision(cg::Vector3d car_position, double car_length);
		int _rand;
		double randomBetween(double min, double max);

		
	};

	
}
#endif
