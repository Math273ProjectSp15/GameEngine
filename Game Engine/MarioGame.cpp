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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	// mario_ texture
	if (!marioTexture_.initialize(graphics, DARK_MARIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario_ texture"));

	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));
	 
	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);

	return;
}

void MarioGame::update()      // must override pure virtual from Game
{
	if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0))
	{
		mario_.setDirection(marioNS::LEFT);
		mario_.setState(marioNS::WALKING);
	}
	else if (input->isKeyDown(RIGHT_KEY) || input->getGamepadDPadRight(0))
	{
		mario_.setDirection(marioNS::RIGHT);
		mario_.setState(marioNS::WALKING);
		if (input->isKeyDown(UP_KEY))
			mario_.setState(marioNS::JUMPING);
	}
	else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		mario_.setState(marioNS::ROLLING);
		//mario_.setCurrentFrame(5);
		//mario_.setFrames(2, 3);
	}
	else if (input->isKeyDown(UP_KEY) || input->getGamepadDPadDown(0))
	{
		mario_.setState(marioNS::JUMPING);
	}
	else
	{
		mario_.setState(marioNS::IDLEING);
	}

	mario_.update(frameTime);
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