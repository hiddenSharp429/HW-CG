#include "MyTrack.h"

namespace tutorial {
	
	
	MyTrack::MyTrack(std::string id) : cg::Group(id) {
	}
	MyTrack::~MyTrack() {
	}
	void MyTrack::createEntities() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		add(new MyTrackPiece2("Piece1", 1, 2, 0));
		add(new MyTrackPiece2("Piece2", 1, 3, 0));
		add(new MyTrackPiece("Piece3", 1, 4, 0));
		add(new MyTrackPiece("Piece4", 0, 4, 180));
		add(new MyTrackPiece("Piece5", 0, 5, 90));
		add(new MyTrackPiece2("Piece6", 1, 5, 90));
		add(new MyTrackPiece2("Piece7", 2, 5, 90));
		add(new MyTrackPiece2("Piece8", 3, 5, 90));
		add(new MyTrackPiece2("Piece9", 4, 5, 90));
		add(new MyTrackPiece("Piece10", 5, 5, 0));
		add(new MyTrackPiece("Piece11", 5, 4, 270));
		add(new MyTrackPiece("Piece12", 4, 4, 90));
		add(new MyTrackPiece("Piece13", 4, 3, 180));
		add(new MyTrackPiece("Piece14", 5, 3, 0));
		add(new MyTrackPiece2("Piece15", 5, 2, 0));
		add(new MyTrackPiece2("Piece16", 5, 1, 0));
		add(new MyTrackPiece("Piece17", 5, 0, 270));
		add(new MyTrackPiece("Piece18", 4, 0, 180));
		add(new MyTrackPiece2("Piece19", 4, 1, 0));
		add(new MyTrackPiece("Piece20", 4, 2, 0));
		add(new MyTrackPiece("Piece21", 3, 2, 180));
		add(new MyTrackPiece2("Piece22", 3, 3, 0));
		add(new MyTrackPiece("Piece23", 3, 4, 0));
		add(new MyTrackPiece("Piece24", 2, 4, 90));
		add(new MyTrackPiece2("Piece25", 2, 3, 0));
		add(new MyTrackPiece2("Piece26", 2, 2, 0));
		add(new MyTrackPiece("Piece27", 2, 1, 180));
		add(new MyTrackPiece("Piece28", 3, 1, 0));
		add(new MyTrackPiece("Piece29", 3, 0, 270));
		add(new MyTrackPiece2("Piece30", 2, 0, 90));
		add(new MyTrackPiece2("Piece31", 1, 0, 90));
		add(new MyTrackPiece("Piece32", 0, 0, 180));
		add(new MyTrackPiece("Piece33", 0, 1, 90));
		add(new MyTrackPiece("Piece34", 1, 1, 270));
		add(new MyObstacle("BallObstacle1", 300, -150));
		add(new MyObstacle("BallObstacle2", 900, -150));
		add(new MyObstacle("BallObstacle3", 900, 150));
		add(new MyObstacle2("MovingObstacle1", 400, 750));
		add(new MyBonus("SpeedBonus1"));
		add(new MyBonus2("DamageBonus1"));
		
		//// Pitbox
		//glColor3d(0.65,0.65,0.65);
		//glPushMatrix();
		//glTranslated(50,50,-.5);
		//glScaled(150,50,1);
		//glutSolidCube(1);		// Top horizontal lane
		//glPopMatrix();
		//glPushMatrix();
		//glTranslated(0,0,-.5);
		//glScaled(50,150,1);
		//glutSolidCube(1);		// Vertical lane
		//glPopMatrix();
		//glPushMatrix();
		//glTranslated(50,-50,-.5);
		//glScaled(150,50,1);
		//glutSolidCube(1);		// Bottom horizontal lane
		//glPopMatrix();
	}


}
