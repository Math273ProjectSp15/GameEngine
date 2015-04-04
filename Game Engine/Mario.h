#pragma once
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace marioNS
{
	const int WIDTH = 97;                  // image width
	const int HEIGHT = 162;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH;     // location on screen
	const int Y = GAME_HEIGHT - HEIGHT;
	const int TEXTURE_COLS = 6;
	const int MARIO_START_FRAME = 0;
	const int MARIO_END_FRAME = 5;
	const float SPEED = 200;                // pixels per second
	const float MASS = 1.0e6f;


}

// inherits from Entity class
class Mario : public Entity
{
public:
	// constructor
	Mario();

	// inherited member functions
	void update(float frameTime, State state, Direction direction);

};