#ifndef MY_BAT_H
#define MY_BAT_H

#include <math.h>
#include <string>
#include "cg/cg.h"

namespace tutorial {

	class MyBat : public cg::Entity,
				  public cg::IDrawListener,
				  public cg::IMouseEventListener
	{
			private:
				cg::Vector2d _position, _size;
				cg::Vector3d _color;

				double _winWidth, _winHeight;
				
				double randomBetween(double min, double max);

			public:
				MyBat(std::string id);
				~MyBat();
				void init();
				void draw();
				void onMouse(int button, int state, int x, int y);
				void onMouseMotion(int x, int y);
				void onMousePassiveMotion(int x, int y);
				
				bool isCollision(cg::Vector2d box_position, cg::Vector2d box_size);

			
	};
}

#endif
