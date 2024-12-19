#include "MyApp.h"

namespace tutorial {

	MyApp::MyApp() : cg::Application("config.ini") {
		_piecesize = cg::Properties::instance()->getDouble("TRACKPIECE_SIZE");
		printf("The game is loading, please stand by...\n");
	}
	MyApp::~MyApp() {
	}
	

		
	void MyApp::createEntities() {
		addEntity(new MyMenu("Menu"));
		addEntity(new MyHud("Hud"));
		addEntity(new MyHud2("Hud2"));
		addEntity(new MyMiniMap("MiniMap"));
		addEntity(new MyCamera());
//		addEntity(new MyTrack("Track"));
		addEntity(new MyRandomTrack("RandomTrack"));
		addEntity(new MyObstacle("BallObstacle1", (_piecesize*4), (_piecesize*5)+(_piecesize/2)));
		addEntity(new MyObstacle("BallObstacle2", (_piecesize*5)+(_piecesize/2), _piecesize));
		addEntity(new MyObstacle("BallObstacle3", (_piecesize*3), (_piecesize/2)));
		addEntity(new MyObstacle2("MovingObstacle1", _piecesize+(_piecesize/6), (_piecesize*4)-(_piecesize/3)));
		addEntity(new MyBonus("SpeedBonus1"));
		addEntity(new MyBonus2("DamageBonus1"));
		addEntity(new MyCar(425,700,"Car1", 1));
		addEntity(new MyCar(475,700,"Car2", 0));
		addEntity(new MyController());
	}
}
