#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyController.h"
#include "MyCar.h"
#include "MyCamera.h"
#include "MyHud.h"
#include "MyHud2.h"
#include "MyMenu.h"
#include "MyMiniMap.h"
#include "MyTrack.h"
#include "MyRandomTrack.h"
#include "MyTrackPiece1.h"
#include "MyTrackPiece2.h"
#include "MyObstacle.h"
#include "MyObstacle2.h"
#include "MyBonus.h"
#include "MyBonus2.h"

namespace tutorial {
	
	class MyApp : public cg::Application {
		
	private:
		double _piecesize;
	
	public:
		MyApp();
		~MyApp();
		void createEntities();
		
	};
}

#endif
