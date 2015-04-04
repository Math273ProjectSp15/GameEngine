#include "MarioGame.h"

// Constructor
MarioGame::MarioGame()
{

}

// Destructor
MarioGame::~MarioGame()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

// Initialize the game
void MarioGame::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	// background_ texture
	if (!backgroundTexture_.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// mario_ texture
	if (!marioTexture_.initialize(graphics, MARIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario_ texture"));

	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, 0, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ball"));

	return;
}

void MarioGame::update()      // must override pure virtual from Game
{
	//Both state and direction must be initialized
	State state = STANDING;
	static Direction direction = RIGHT; //Static because direction persists

	if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0))
	{
		mario_.setX(mario_.getX() - marioNS::SPEED*frameTime);
		state = WALKING;
		direction = LEFT;
		mario_.setFrames(1, 3);
	}
	else if (input->isKeyDown(RIGHT_KEY) || input->getGamepadDPadRight(0))
	{
		mario_.setX(mario_.getX() + marioNS::SPEED*frameTime);
		state = WALKING;
		direction = RIGHT;
		mario_.setFrames(1, 3);
	}
	else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		state = CROUCHING;
		mario_.setCurrentFrame(6);
		mario_.setFrames(6, 6);
	}
	else
	{
		mario_.setCurrentFrame(0);
	}

	mario_.update(frameTime, state, direction);
}

void MarioGame::ai()          // "
{

}

void MarioGame :: collisions()  // "
{
	/*VECTOR2 cv;
	if (ball.collidesWith(paddle, cv))
		ball.bounce(cv, paddle);*/
}
void MarioGame :: render()      // "
{
	graphics->spriteBegin();                // begin drawing sprites

	background_.draw();                        // add the background to the scene
	mario_.draw();                          // add mario to the scene
	graphics->spriteEnd();                  // end drawing sprites
}
void MarioGame :: releaseAll()
{
	marioTexture_.onLostDevice();           // mario texture
	backgroundTexture_.onLostDevice();         // background texture

	Game::releaseAll();
	return;
}

void MarioGame :: resetAll()
{
	backgroundTexture_.onResetDevice();
	marioTexture_.onResetDevice();

	Game::resetAll();
	return;
}