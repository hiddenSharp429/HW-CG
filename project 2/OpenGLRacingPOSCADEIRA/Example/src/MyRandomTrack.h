#ifndef MY_RANDOM_TRACK_H
#define MY_RANDOM_TRACK_H

#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "cg/cg.h"
#include "MyTrackPiece1.h"
#include "MyTrackPiece2.h"
#include "MyObstacle.h"
#include "MyObstacle2.h"
#include "MyBonus.h"
#include "MyBonus2.h"

namespace tutorial {

	class MyRandomTrack : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupReshapeEvent
	{
	private:
		int max_map_lines, max_map_columns;
	protected:
		void createEntities();

		
	public:
		MyRandomTrack(std::string id);
		~MyRandomTrack();
		
	};

	
}
#endif
