#ifndef MY_TRACK_H
#define MY_TRACK_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyTrackPiece1.h"
#include "MyTrackPiece2.h"
#include "MyObstacle.h"
#include "MyObstacle2.h"
#include "MyBonus.h"
#include "MyBonus2.h"

namespace tutorial {

	class MyTrack : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupReshapeEvent
	{
	private:
		double _winWidth, _winHeight;
	protected:
		void createEntities();

		
	public:
		MyTrack(std::string id);
		~MyTrack();
		
	};

	
}
#endif
