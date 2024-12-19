#ifndef MY_BOX_H
#define MY_BOX_H

#include <math.h>
#include <string>
#include "cg/cg.h"
#include "MyBat.h"

namespace tutorial {

	class MyBox : public cg::Entity,
				  public cg::IDrawListener,
				  public cg::IUpdateListener
	{
	private:
		cg::Vector2d _position, _size, _velocity;
		cg::Vector3d _color;
		double _winWidth, _winHeight;
		
		double randomBetween(double min, double max);
		
		MyBat* _bat;
		
	public:
		MyBox(std::string id);
		~MyBox();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
	};
}
#endif

