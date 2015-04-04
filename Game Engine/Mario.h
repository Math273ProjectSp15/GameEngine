#pragma once
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace marioNS
{
	const int WIDTH = 50;                  // image width
	const int HEIGHT = 100;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH;     // location on screen
	const int Y = GAME_HEIGHT - HEIGHT;
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