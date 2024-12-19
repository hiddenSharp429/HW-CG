#ifndef MY_MINI_MAP_H
#define MY_MINI_MAP_H

#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "MyTrack.h"
#include "MyCar.h"
#include "MyCamera.h"

namespace tutorial {

	class MyMiniMap : public cg::Entity,
		public cg::IDrawOverlayListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener

	{
	private:
		double _winWidth, _winHeight;

		MyCamera* _cam;
		MyCar* _car1;
		MyCar* _car2;
		MyTrack* _track;


	public:
		MyMiniMap(std::string id);
		~MyMiniMap();

		void init();
		void update(unsigned long elapsed_millis);
		void drawOverlay();
		void onReshape(int width, int height);

	};

	
}
#endif
