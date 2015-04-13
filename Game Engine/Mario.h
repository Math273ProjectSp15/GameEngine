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

	const int WALKING_IMAGE_WIDTH = 256;
	const int WALKING_IMAGE_HEIGHT = 256;
	const int WALKING_TEXTURE_COLS = 5;
	const int WALKING_MARIO_START_FRAME = 10;
	const int WALKING_MARIO_END_FRAME = 14;
	const float WALKING_ANIMATION_DELAY = 0.15f;

	const int ROLLING_IMAGE_WIDTH = 128;
	const int ROLLING_IMAGE_HEIGHT = 128;
	const int ROLLING_TEXTURE_COLS = 2;
	const int ROLLING_MARIO_START_FRAME = 0;
	const int ROLLING_MARIO_END_FRAME = 3;
	const float ROLLING_ANIMATION_DELAY = 0.1f;

	const int JUMP_UP_IMAGE_WIDTH = 128;
	const int JUMP_UP_IMAGE_HEIGHT = 256;
	const int JUMP_UP_TEXTURE_COLS = 6;
	const int JUMP_UP_MARIO_START_FRAME = 5;
	const int JUMP_UP_MARIO_END_FRAME = 4;
	const float JUMP_UP_ANIMATION_DELAY = 1.0f;

	const int JUMP_FALL_IMAGE_WIDTH = 256;
	const int JUMP_FALL_IMAGE_HEIGHT = 256;
	const int JUMP_FALL_TEXTURE_COLS = 4;
	const int JUMP_FALL_MARIO_START_FRAME = 3;
	const int JUMP_FALL_MARIO_END_FRAME = 3;
	const float JUMP_FALL_ANIMATION_DELAY = 1.0f;

	enum State
	{
		IDLEING,
		WALKING,
		ROLLING,
		JUMPING,
	};

	enum Direction
	{
		LEFT,
		RIGHT,
		STATIONARY
	};

}

// inherits from Entity class
class Mario : public Entity
{
private:
	Image marioWalking_;
	Image marioRolling_;
	Image marioJumpUp_;
	Image marioJumpFall_;

public:
	// constructor
	Mario();

	// inherited member functions
	virtual void draw();
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