// Updated 2010 by J M Brisson Lopes (Mac OS X support)

#include <ctime>
#include "cg/cg.h"
#include "MyApp.h"

int main(int argc, char** argv) {

	srand(time(0));
	cg::Manager::instance()->runApp(new tutorial::MyApp(),60,argc,argv);
	return 0;
}