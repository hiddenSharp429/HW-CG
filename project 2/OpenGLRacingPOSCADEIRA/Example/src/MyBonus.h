#ifndef MY_BONUS_H
#define MY_BONUS_H

#include <string>
#include "cg/cg.h"


namespace tutorial {

	class MyBonus : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;
		int _transx, _transy;
		double _piecesize;
		
	public:
		MyBonus(std::string id);
		~MyBonus();
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
