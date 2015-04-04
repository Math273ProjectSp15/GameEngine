#include "Mario.h"

Mario::Mario() : Entity()
{
	spriteData.width = marioNS::WIDTH;         // size of Ship1
	spriteData.height = marioNS::HEIGHT;
	spriteData.x = marioNS::X;                 // location on screen
	spriteData.y = marioNS::Y;
	spriteData.rect.bottom = marioNS::HEIGHT;  // rectangle to select parts of an image
	spriteData.rect.right = marioNS::WIDTH;
	frameDelay = 0.1;
	startFrame = 0;                             // first frame of animation
	endFrame = 0;                           // last frame of animation
	currentFrame = startFrame;
	edge.top = -marioNS::HEIGHT / 2;             // set collision edges
	edge.bottom = marioNS::HEIGHT / 2;
	edge.left = -marioNS::WIDTH / 2;
	edge.right = marioNS::WIDTH / 2;
	collisionType = entityNS::ROTATED_BOX;
	mass = marioNS::MASS;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Mario::update(float frameTime, State state, Direction direction)
{
	Entity::update(frameTime);

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - marioNS::WIDTH)  // if hit right screen edge
		spriteData.x = GAME_WIDTH - marioNS::WIDTH;  // position at right screen edge
	else if (spriteData.x < 0)                    // else if hit left screen edge
		spriteData.x = 0;                           // position at left screen edge
	spriteData.state = state;
	spriteData.direction = direction;
	if (state == CROUCHING)
	{
		edge.top = (-marioNS::HEIGHT / 2) / 3;             // set collision edges for crouching mario
	}
	else
	{
		edge.top = -marioNS::HEIGHT / 2;             // reset collision edges
	}
}
