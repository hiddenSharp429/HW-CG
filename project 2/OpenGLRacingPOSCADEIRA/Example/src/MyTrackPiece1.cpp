#include "MyTrackPiece1.h"

namespace tutorial {
	
	
	MyTrackPiece1::MyTrackPiece1(std::string id, double transx, double transy, double rotation) : cg::Entity(id) {
		_rot = rotation;
		_coordx = transx;
		_coordy = transy;

	}
	MyTrackPiece1::~MyTrackPiece1() {
	}


	void MyTrackPiece1::init() {
//		_size = cg::Properties::instance()->getVector2d("BAT_SIZE");
		cg::tWindow win = cg::Manager::instance()->getApp()->getWindow();
		_winWidth = win.width;
		_winHeight = win.height;
		pObj = gluNewQuadric();
		
		_drawroadlines = cg::Properties::instance()->getInt("DRAW_ROAD_LINES");
		_piecesize = cg::Properties::instance()->getDouble("TRACKPIECE_SIZE");
		

		texture = SOIL_load_OGL_texture
					(
						"textures/grass.bmp",
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | /*SOIL_FLAG_NTSC_SAFE_RGB |*/ SOIL_FLAG_COMPRESS_TO_DXT
					);
		texture2 = SOIL_load_OGL_texture
					(
						"textures/dirt.bmp",
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | /*SOIL_FLAG_NTSC_SAFE_RGB |*/ SOIL_FLAG_COMPRESS_TO_DXT
					);
		
		// Links for velocity/points updates
		_car1 = (MyCar*)cg::Registry::instance()->get("Car1");
		_car2 = (MyCar*)cg::Registry::instance()->get("Car2");	

	}

	void MyTrackPiece1::update(unsigned long elapsed_millis) {

		// Set the cars' maximum velocity according to the type of pavement each one is being driven on	
		if(_rot == 0) {
			if( (_car1->_coordx == _coordx) && (_car1->_coordy == _coordy) )
				if(-(_car1->_position[0]-(_car1->_coordx)*_piecesize) < (_car1->_position[1]-(_car1->_coordy+1)*_piecesize) ) {
					_car1->_updateVel = true;
				}
				else
					_car1->_updateVel = false;
			if( (_car2->_coordx == _coordx) && (_car2->_coordy == _coordy) )
				if( -(_car2->_position[0]-(_car2->_coordx)*_piecesize) < (_car2->_position[1]-(_car2->_coordy+1)*_piecesize) ) {
					_car2->_updateVel = true;
				}
				else
					_car2->_updateVel = false;
		}
		if(_rot == 90) {
			if( (_car1->_coordx == _coordx) && (_car1->_coordy == _coordy) )
				if( (_car1->_position[0]-(_car1->_coordx)*_piecesize) < (_car1->_position[1]-(_car1->_coordy)*_piecesize) ) {
					_car1->_updateVel = true;
				}
				else
					_car1->_updateVel = false;
			if( (_car2->_coordx == _coordx) && (_car2->_coordy == _coordy) )
				if( (_car2->_position[0]-(_car2->_coordx)*_piecesize) < (_car2->_position[1]-(_car2->_coordy)*_piecesize) ) {
					_car2->_updateVel = true;
				}
				else
					_car2->_updateVel = false;
		}
		if(_rot == 180) {
			if( (_car1->_coordx == _coordx) && (_car1->_coordy == _coordy) )				
				if( (_car1->_position[0]-(_car1->_coordx)*_piecesize) < -(_car1->_position[1]-(_car1->_coordy+1)*_piecesize) ) {
					_car1->_updateVel = true;
				}
				else
					_car1->_updateVel = false;
			if( (_car2->_coordx == _coordx) && (_car2->_coordy == _coordy) )
				if( (_car2->_position[0]-(_car2->_coordx)*_piecesize) < -(_car2->_position[1]-(_car2->_coordy+1)*_piecesize) ) {
					_car2->_updateVel = true;
				}
				else
					_car2->_updateVel = false;
		}
		if(_rot == 270) {
			if( (_car1->_coordx == _coordx) && (_car1->_coordy == _coordy) )
				if( -(_car1->_position[0]-(_car1->_coordx)*_piecesize) < -(_car1->_position[1]-(_car1->_coordy)*_piecesize) ) {
					_car1->_updateVel = true;
				}
				else
					_car1->_updateVel = false;
			if( (_car2->_coordx == _coordx) && (_car2->_coordy == _coordy) )
				if( -(_car2->_position[0]-(_car2->_coordx)*_piecesize) < -(_car2->_position[1]-(_car2->_coordy)*_piecesize) ) {
					_car2->_updateVel = true;
				}
				else
					_car2->_updateVel = false;
		}
				
	}

	void MyTrackPiece1::draw() {

		float specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		float fDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse);
		float fAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, fAmbient);		
		
		static GLfloat n[6][3] = { {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
									{1.0, 0.0, 0.0}, {0.0, -1.0, 0.0},
									{0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
		static GLint faces[6][4] = { {0, 1, 2, 3}, {3, 2, 6, 7},
									{7, 6, 5, 4}, {4, 5, 1, 0},
									{5, 6, 2, 1}, {7, 4, 0, 3} };
		GLfloat v[8][3];
		GLint i;

		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -_piecesize / 2;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = _piecesize / 2;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -_piecesize / 2;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = _piecesize / 2;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = -20 / 2;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = 20 / 2;
		// No need to draw a green shape for every single track piece, since the background already is green! ( + these green shapes weren't being lit)
		//glColor3d(0.0,0.7,0.0);
		glPushMatrix();
		glTranslated((_piecesize/2)+_piecesize*_coordx,(_piecesize/2)+_piecesize*_coordy, -11); // Change from -10 to -11 to appear below the pitstop
		//glScaled(_piecesize,_piecesize,20);
		glEnable(GL_TEXTURE_2D);
		for (i = 5; i >= 0; i--) {
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
		
		glPushMatrix();
		
	//	float fDiffuse2[] = {0.65f, 0.65f, 0.65f, 1.};
	//	glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse2);
		
		switch (_rot) {
			case 0 : {
				glTranslated(_piecesize*_coordx, _piecesize*_coordy, 0);
				break;
				}
			case 90 : {
				glTranslated(_piecesize*(_coordx+1), _piecesize*(_coordy), 0);
				break;
			}
			case 180 : {
				glTranslated(_piecesize*(_coordx+1), _piecesize*(_coordy+1), 0);
				break;
			}
			case 270 : {
				glTranslated(_piecesize*(_coordx), _piecesize*(_coordy+1), 0);
				break;
			}
		}
		glBindTexture(GL_TEXTURE_2D, texture2);
		gluQuadricDrawStyle(pObj, GLU_FILL);
		gluQuadricTexture(pObj, GL_TRUE);
		glRotated(_rot, 0,0,1);
		gluPartialDisk(pObj,(_piecesize/3),(_piecesize/1.5),20,10,0,90);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
		//Linhas da estrada
		if(_drawroadlines)
			switch (_rot) {
				case 0 : {
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2), _piecesize*_coordy, -0.4);
					glRotated(0, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2.4), _piecesize*_coordy+(_piecesize/4), -0.4);
					glRotated(30, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/4), _piecesize*_coordy+(_piecesize/2.4), -0.4);
					glRotated(60, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx, _piecesize*_coordy+(_piecesize/2), -0.4);
					glRotated(90, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
					break;
					}
				case 90 : {
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2), _piecesize*_coordy, -0.4);
					glRotated(0, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/1.71428571), _piecesize*_coordy+(_piecesize/4), -0.4);
					glRotated(-30, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/(4/3)), _piecesize*_coordy+(_piecesize/2.4), -0.4);
					glRotated(-60, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+_piecesize, _piecesize*_coordy+(_piecesize/2), -0.4);
					glRotated(-90, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
					break;
				}
				case 180 : {
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2), _piecesize*_coordy+_piecesize, -0.4);
					glRotated(0, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/1.71428571), _piecesize*_coordy+(_piecesize/(4/3)), -0.4);
					glRotated(30, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/(4/3)), _piecesize*_coordy+(_piecesize/1.71428571), -0.4);
					glRotated(60, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+_piecesize, _piecesize*_coordy+(_piecesize/2), -0.4);
					glRotated(90, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
					break;
				}
				case 270 : {
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2), _piecesize*_coordy+_piecesize, -0.4);
					glRotated(0, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/2.4), _piecesize*_coordy+(_piecesize/(4/3)), -0.4);
					glRotated(-30, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx+(_piecesize/4), _piecesize*_coordy+(_piecesize/1.71428571), -0.4);
					glRotated(-60, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
				
					glPushMatrix();
					glTranslated(_piecesize*_coordx, _piecesize*_coordy+(_piecesize/2), -0.4);
					glRotated(-90, 0,0,1);
					glScaled(5,10,1);
					glutSolidCube(1);
					glPopMatrix();
					break;
				}
			}
		
		// Return back to default values
		float specularDefault[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularDefault);
		float fDiffuseDefault[] = {0.8f, 0.8f, 0.8f, 1.0f};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuseDefault);
		float fAmbientDefault[] = {0.2f, 0.2f, 0.2f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, fAmbientDefault);

	}
	
	void MyTrackPiece1::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}	

}
