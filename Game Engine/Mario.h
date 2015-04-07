#pragma once
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "cmath"

namespace marioNS
{
	const int WIDTH = 128;   ///128               // image width
	const int HEIGHT = 256;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH ;     // location on screen
	const int Y = GAME_HEIGHT - HEIGHT ;
	const int TEXTURE_COLS = 12; //12
	const int IDLE_MARIO_START_FRAME = 12; //12
	const int IDLE_MARIO_END_FRAME = 23;  //23
	const float SPEED = 200;                // pixels per second
	const float MASS = 1.0e6f;
	const int RUNNING_IMAGE_WIDTH = 256;
	const int RUNNING_IMAGE_HEIGHT = 256;
	const int RUNNING_TEXTURE_COLS = 5;
	const int RUNNING_MARIO_START_FRAME = 10;
	const int RUNNING_MARIO_END_FRAME = 14;

	enum State
	{
		IDLEING,
		WALKING,
		CROUCHING,
		JUMPING,
	};

	enum Direction
	{
		LEFT,
		RIGHT
	};

}

// inherits from Entity class
class Mario : public Entity
{
private:
	Image marioRunning;

public:
	// constructor
	Mario();

	// inherited member functions
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);

	// inherited member functions
	void update(float frameTime);
	
	void setState(marioNS::State state);
	marioNS::State getState();

	void setDirection(marioNS::Direction direction);
	marioNS::Direction getDirection();

protected:
	marioNS::State state_;
	marioNS::Direction direction_;
	
	
};