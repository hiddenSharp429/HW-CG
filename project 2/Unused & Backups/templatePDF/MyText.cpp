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
// Updated 2011 03 22 by J M Brisson Lopes
//            - corrected loop statement in messageLength and drawMessage

#include "MyText.h"

#include <iostream>

namespace tutorial {

	MyText::MyText(std::string id) : cg::Entity(id) {
	}
	MyText::~MyText() {
	}
	void MyText::init() {
		_helloMessage   = "Hello World!";
		_buildNoMessage = "This is CGLib build 24 bis";
		_helloFont = GLUT_BITMAP_HELVETICA_18;
		_buildFont = GLUT_BITMAP_HELVETICA_12;
		int windowWidth    = cg::Manager::instance()->getApp()->getWindow().width;
		int windowHeight   = cg::Manager::instance()->getApp()->getWindow().height;
		int length = messageLength( _helloMessage, _helloFont);
		_helloXpos = (windowWidth - length) / 2;
		_helloYpos =  windowHeight *3 / 4;
		length = messageLength( _buildNoMessage, _buildFont);
		_buildXpos = (windowWidth - length) / 2;
		_buildYpos =  windowHeight /2;
	}
	void MyText::draw() {
		drawMessage( _helloMessage,   _helloFont, _helloXpos, _helloYpos);
		drawMessage( _buildNoMessage, _buildFont, _buildXpos, _buildYpos);
	}
	
	int MyText::messageLength( std::string message, void * font)
	{
		int length = 0;
		for (std::size_t i = 0; i < message.size(); i++)
            length += glutBitmapWidth( font, message[i]);
		return length;
	}
	
	void MyText::drawMessage( std::string message, void * font, int x, int y)
	{
		glRasterPos2i( x, y);
		for (std::size_t i = 0; i < message.size(); i++)
            glutBitmapCharacter( font, message[i]);
	}
}