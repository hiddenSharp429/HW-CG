// This file is part of CGLib project template.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2010 IST & J M Brisson Lopes

#ifndef MY_TEXT_H
#define MY_TEXT_H

#include <string>
#include "cg/cg.h"

namespace tutorial {

	class MyText : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		std::string  _helloMessage,  _buildNoMessage;
		void        *_helloFont,    *_buildFont;
		int          _helloXpos,     _helloYpos,
	                 _buildXpos,     _buildYpos;
		double       _windowWidth,   _windowHeight;

	public:
		MyText(std::string id);
		~MyText();
		void init();
		void draw();
		
	private:
		int  messageLength( std::string message, void * font);
		void drawMessage( std::string message, void * font, int x, int y);
	};
}

#endif