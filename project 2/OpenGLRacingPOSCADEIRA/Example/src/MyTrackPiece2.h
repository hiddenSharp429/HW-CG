#ifndef MY_TRACK_PIECE2_H
#define MY_TRACK_PIECE2_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "cg/cg.h"
#include "MyCar.h"
#include "SOIL.h"

namespace tutorial {

	class MyTrackPiece2 : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		int _coordx, _coordy, _rot;
		double _piecesize;

		GLuint texture, texture2;
		
		MyCar* _car1;
		MyCar* _car2;
		
		int _drawroadlines;


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
