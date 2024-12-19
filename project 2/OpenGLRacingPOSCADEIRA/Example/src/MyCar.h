#ifndef MY_CAR_H
#define MY_CAR_H

#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "cg/cg.h"
#include "MyBonus.h"
#include "MyBonus2.h"
#include "glm.h"

// Particle system
#define ParticleCount 50

// 3D model
#define MAX_VERTICES 8000 // Max number of vertices (for each object)
#define MAX_POLYGONS 8000 // Max number of polygons (for each object)

namespace tutorial {

	class MyCar : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener
	{
	private:
		cg::Vector3d _size, _color;
		
		bool _upKeyPressed, _upKeyReleased, _leftKeyPressed, _leftKeyReleased, _rightKeyPressed, _rightKeyReleased, _downKeyPressed, _downKeyReleased;

		int _use3dmodels;

		double _radius, _winWidth, _winHeight, _acceleration, _maxvel, _initmaxvel, _posx, _posy;
		
		double _piecesize;

		double randomBetween(double min, double max);
		
		GLuint raw_texture_load(const char *filename, int width, int height);
		GLuint texturelol;
	
		GLMmodel* model;


	public:
		MyCar(std::string id);
		MyCar(double posx, double posy, std::string id, int cor);
		~MyCar();
		MyBonus* _speedBonus1;
		MyBonus2* _damageBonus1;
		double width, length, height, _velocity, _collisionVelocity, _elapsedTime, _angle, _collisionAngle, _speedBonusTime, _damageBonusTime;
		int _coordx, _coordy;
		int _dano, _points, _cor;
		bool  _colliding, _speedBonus, _damageBonus, _minimapMode, _updateVel;
		cg::Vector3d _position;
		cg::Vector3d getPosition();
		void setPosition(int coord);
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		
		bool isUpKeyPressed();
		void setUpKeyPressed(bool val);
		bool isUpKeyReleased();
		void setUpKeyReleased(bool val);
		bool isLeftKeyPressed();
		void setLeftKeyPressed(bool val);
		bool isLeftKeyReleased();
		void setLeftKeyReleased(bool val);
		bool isRightKeyPressed();
		void setRightKeyPressed(bool val);
		bool isRightKeyReleased();
		void setRightKeyReleased(bool val);
		bool isDownKeyPressed();
		void setDownKeyPressed(bool val);
		bool isDownKeyReleased();
		void setDownKeyReleased(bool val);
		
		
		GLfloat texture[10];

		typedef struct {
			double Xpos;
			double Ypos;
			double Zpos;
			double Xmov;
			double Zmov;
			double Red;
			double Green;
			double Blue;
			double Direction;
			double Acceleration;
			double Deceleration;
			double Scalez;
			bool Visible;
		} PARTICLES;

		PARTICLES Particle[ParticleCount];

		GLuint LoadTextureRAW( const char * filename, int width, int height);
		void FreeTexture( GLuint texturez );
		
	};
}

#endif
