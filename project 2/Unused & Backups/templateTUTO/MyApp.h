#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyBat.h"
#include "MyBoxManager.h"
#include "MyCamera.h"
#include "MyController.h"

namespace tutorial {

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
	};
}

#endif