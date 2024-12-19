#ifndef MY_TRACK_PIECE2_H
#define MY_TRACK_PIECE2_H

#include <string>
#include "cg/cg.h"
//#include "MyCar.h"
#include <stdio.h>
#include <stdlib.h>
#include "MyRawLoader.h"

namespace tutorial {

	class MyTrackPiece2 : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		int _coordx, _coordy, _rot;
//		MyCar *_car;

		GLuint texture, texture2;
		
		
		
	public:
		MyTrackPiece2(std::string id, double transx, double transy, double rotation);
		~MyTrackPiece2();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
        void onReshape(int width, int height);


		
	};

	
}
#endif
