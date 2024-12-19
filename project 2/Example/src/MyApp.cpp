#include "MyApp.h"

namespace tutorial {

	MyApp::MyApp() : cg::Application("config.ini") {
	}
	MyApp::~MyApp() {
	}
	

		
	void MyApp::createEntities() {
		addEntity(new MyMenu("Menu"));
		addEntity(new MyHud("Hud"));
		addEntity(new MyHud2("Hud2"));
		addEntity(new MyMiniMap("MiniMap"));
		addEntity(new MyCamera());
//		addEntity(new MyTrack("Track1"));
		addEntity(new MyTrackPiece2("Piece1", 1, 2, 0));
		addEntity(new MyTrackPiece2("Piece2", 1, 3, 0));
		addEntity(new MyTrackPiece("Piece3", 1, 4, 0));
		addEntity(new MyTrackPiece("Piece4", 0, 4, 180));
		addEntity(new MyTrackPiece("Piece5", 0, 5, 90));
		addEntity(new MyTrackPiece2("Piece6", 1, 5, 90));
		addEntity(new MyTrackPiece2("Piece7", 2, 5, 90));
		addEntity(new MyTrackPiece2("Piece8", 3, 5, 90));
		addEntity(new MyTrackPiece2("Piece9", 4, 5, 90));
		addEntity(new MyTrackPiece("Piece10", 5, 5, 0));
		addEntity(new MyTrackPiece("Piece11", 5, 4, 270));
		addEntity(new MyTrackPiece("Piece12", 4, 4, 90));
		addEntity(new MyTrackPiece("Piece13", 4, 3, 180));
		addEntity(new MyTrackPiece("Piece14", 5, 3, 0));
		addEntity(new MyTrackPiece2("Piece15", 5, 2, 0));
		addEntity(new MyTrackPiece2("Piece16", 5, 1, 0));
		addEntity(new MyTrackPiece("Piece17", 5, 0, 270));
		addEntity(new MyTrackPiece("Piece18", 4, 0, 180));
		addEntity(new MyTrackPiece2("Piece19", 4, 1, 0));
		addEntity(new MyTrackPiece("Piece20", 4, 2, 0));
		addEntity(new MyTrackPiece("Piece21", 3, 2, 180));
		addEntity(new MyTrackPiece2("Piece22", 3, 3, 0));
		addEntity(new MyTrackPiece("Piece23", 3, 4, 0));
		addEntity(new MyTrackPiece("Piece24", 2, 4, 90));
		addEntity(new MyTrackPiece2("Piece25", 2, 3, 0));
		addEntity(new MyTrackPiece2("Piece26", 2, 2, 0));
		addEntity(new MyTrackPiece("Piece27", 2, 1, 180));
		addEntity(new MyTrackPiece("Piece28", 3, 1, 0));
		addEntity(new MyTrackPiece("Piece29", 3, 0, 270));
		addEntity(new MyTrackPiece2("Piece30", 2, 0, 90));
		addEntity(new MyTrackPiece2("Piece31", 1, 0, 90));
		addEntity(new MyTrackPiece("Piece32", 0, 0, 180));
		addEntity(new MyTrackPiece("Piece33", 0, 1, 90));
		addEntity(new MyTrackPiece("Piece34", 1, 1, 270));
		addEntity(new MyObstacle("BallObstacle1", 1200, 1650));
		addEntity(new MyObstacle("BallObstacle2", 1650, 300));
		addEntity(new MyObstacle("BallObstacle3", 900, 150));
		addEntity(new MyObstacle2("MovingObstacle1", 350, 1100));
		addEntity(new MyBonus("SpeedBonus1"));
		addEntity(new MyBonus2("DamageBonus1"));
		addEntity(new MyCar(425,700,"Car1", 1));
		addEntity(new MyCar(475,700,"Car2", 0));
		addEntity(new MyController());
	}
}
