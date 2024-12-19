#include "MyTrackPiece2.h"

namespace tutorial {
	
	
	MyTrackPiece2::MyTrackPiece2(std::string id, double transx, double transy, double rotation) : cg::Entity(id) {
		_rot = rotation;
		_coordx = transx;
		_coordy = transy;

	}
	MyTrackPiece2::~MyTrackPiece2() {
	}


	void MyTrackPiece2::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;

		
		// Link for collisions
		//_car = (MyCar*)cg::Registry::instance()->get("Car1");
		MyRawLoader _rawldr;
		texture = _rawldr.LoadRawImage("textures/grass.raw", 256, 256);
		texture2 = _rawldr.LoadRawImage("textures/dirt.raw", 256, 256);

	}

	void MyTrackPiece2::update(unsigned long elapsed_millis) {
	}

	void MyTrackPiece2::draw() {
		
		static GLfloat n[6][3] = { {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
									{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
									{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
		static GLint faces[6][4] = { {0, 1, 2, 3}, {3, 2, 6, 7},
									{7, 6, 5, 4}, {4, 5, 1, 0},
									{5, 6, 2, 1}, {7, 4, 0, 3} };
		GLfloat v[8][3];
		GLint i;

		// Grass
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -300 / 2;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 300 / 2;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -300 / 2;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = 300 / 2;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = -20 / 2;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = 20 / 2;
		// No need to draw a green shape for every single track piece, since the background already is green! ( + these green shapes weren't being lit)
		//glColor3d(0.0,0.7,0.0);
		glPushMatrix();
		glTranslated(150+300*_coordx,150+300*_coordy, -11); // Change from -10 to -11 to appear below the pitstop
		//glScaled(300,300,20);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		for (i = 5; i >= 0; i--) {
			glBegin(GL_QUADS);
				glNormal3fv(&n[i][0]);
				glTexCoord2f(0.0, 0.0);
				glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(2.0, 0.0);
				glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(2.0, 2.0);
				glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0.0, 2.0);
				glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
		
		glPopMatrix();

		// Road
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -100 / 2;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 100 / 2;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -300 / 2;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = 300 / 2;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = -2 / 2;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = 2 / 2;		
		glPushMatrix();
		//glColor3d(0.65,0.65,0.65);
		switch (_rot) {
			case 0 : {
				glTranslated(300*_coordx+150, 300*_coordy+150, -1);
				break;
				}
			case 90 : {
				glTranslated(300*(_coordx)+150, 300*(_coordy)+150, -1);
				break;
			}

		}
		glBindTexture(GL_TEXTURE_2D, texture2);
		glRotated(_rot, 0,0,1);
		//glScaled(100,300,1);
		for (i = 5; i >= 0; i--) {
			glBegin(GL_QUADS);
				glNormal3fv(&n[i][0]);
				glTexCoord2f(0.0, 0.0);
				glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(4.0, 0.0);
				glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(4.0, 1.0);
				glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0.0, 1.0);
				glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
		//Linhas da estrada
		glColor3d(0.9,0.9,0.9);
		
		switch (_rot) {
			case 0 : {
				glPushMatrix();
				glTranslated(300*_coordx+150, 300*_coordy, -0.4);
				glRotated(0, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+150, 300*_coordy+100, -0.4);
				glRotated(0, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+150, 300*_coordy+200, -0.4);
				glRotated(0, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+150, 300*_coordy+300, -0.4);
				glRotated(0, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				break;
				}
			case 90 : {
				glPushMatrix();
				glTranslated(300*_coordx, 300*_coordy+150, -0.4);
				glRotated(90, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+100, 300*_coordy+150, -0.4);
				glRotated(90, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+200, 300*_coordy+150, -0.4);
				glRotated(90, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				
				glPushMatrix();
				glTranslated(300*_coordx+300, 300*_coordy+150, -0.4);
				glRotated(90, 0,0,1);
				glScaled(5,10,1);
				glutSolidCube(1);
				glPopMatrix();
				break;
			}
			
		}


	}
	
	void MyTrackPiece2::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}	

}
