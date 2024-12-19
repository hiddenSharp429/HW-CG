#include "MyApp.h"

namespace tutorial {

	MyApp::MyApp() : cg::Application("config.ini") {
		_window.caption = "Tutorial";
		_window.width = 800;
		_window.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity(new MyCamera());
		addEntity(new MyBoxManager("BoxManager"));
		addEntity(new MyBat("Bat"));
		addEntity(new MyController());
	}
}