#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"
#include "MyCar.h"

namespace tutorial {

    class MyCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;
		MyCar* _car1;
		MyCar* _car2;

    public:
        MyCamera();
        virtual ~MyCamera();
        void init();
        void draw();
        int _numplayers;
        void onReshape(int width, int height);
    };
}

#endif
