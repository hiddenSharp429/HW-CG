#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"

namespace tutorial {

	class MyController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		MyController();
		~MyController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
	};
}

#endif