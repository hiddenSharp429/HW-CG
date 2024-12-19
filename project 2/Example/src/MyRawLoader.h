#ifndef MY_RAW_LOADER_H
#define MY_RAW_LOADER_H

#include <string>
#include "cg/cg.h"
#include <stdio.h>
#include <stdlib.h>

namespace tutorial {

	class MyRawLoader
	{
	private:

	public:
		MyRawLoader();
		~MyRawLoader();

		GLuint LoadRawImage(const char *filename, int width, int height);

		
	};

	
}
#endif
