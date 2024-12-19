#ifndef MY_CAR_H
#define MY_CAR_H

#include <string>
#include "cg/cg.h"

namespace tutorial {

	class MyCar : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener
	{
	private:
		cg::Vector3d _size, _color, _position;
		
		bool _upKeyPressed, _upKeyReleased, _leftKeyPressed, _leftKeyReleased, _rightKeyPressed, _rightKeyReleased, _downKeyPressed, _downKeyReleased;

		double width, length, height, _angle, _radius, _winWidth, _winHeight, _velocity, _acceleration;

		double randomBetween(double min, double max);
		


	public:
		MyCar(std::string id);
		~MyCar();
		cg::Vector3d getPosition();
		void setPosition(int coord);
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		
		bool isUpKeyPressed();
		void setUpKeyPressed(bool val);
		bool isUpKeyReleased();
		void setUpKeyReleased(bool val);
		bool isLeftKeyPressed();
		void setLeftKeyPressed(bool val);
		bool isLeftKeyReleased();
		void setLeftKeyReleased(bool val);
		bool isRightKeyPressed();
		void setRightKeyPressed(bool val);
		bool isRightKeyReleased();
		void setRightKeyReleased(bool val);
		bool isDownKeyPressed();
		void setDownKeyPressed(bool val);
		bool isDownKeyReleased();
		void setDownKeyReleased(bool val);
	};
}

#endif
