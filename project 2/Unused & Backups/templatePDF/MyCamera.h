#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace tutorial {

	class MyCamera : public cg::Entity, public cg::IDrawListener {
	private:
		double _winWidth, _winHeight;
	
	public:
		MyCamera();
		virtual ~MyCamera();
		void init();
		void draw();
	};
	
}

#endif
