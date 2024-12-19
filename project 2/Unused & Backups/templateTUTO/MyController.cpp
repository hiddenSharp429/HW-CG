#include "MyController.h"

namespace tutorial {

	MyController::MyController() : cg::Entity("Controller") {

	}
	MyController::~MyController() {
	}
	void MyController::init() {
	}
	void MyController::onKeyPressed(unsigned char key) {
        if (key == 27) {
			cg::Manager::instance()->shutdownApp();
        }
	}
	void MyController::onKeyReleased(unsigned char key) {
        if (key == ' ') {
			cg::Registry::instance()->get("BoxManager")->state.toggle();
        }
	}
	void MyController::onSpecialKeyPressed(int key) {
	}
	void MyController::onSpecialKeyReleased(int key) {
        if (key == GLUT_KEY_F1) {
			cg::Manager::instance()->getApp()->dump();
        }
	}

}