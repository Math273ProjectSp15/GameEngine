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
	background_.setY(-MAP_HEIGHT + (int)GAME_HEIGHT);

	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));
	 
	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);

	return;
}

void MarioGame::update()      // must override pure virtual from Game
{
	// move background_ in X direction opposite mario_
	background_.setX(background_.getX() - frameTime * mario_.getVelocity().x);

	// move background_ in Y direction opposite mario_
	background_.setY(background_.getY() - frameTime * mario_.getVelocity().y);
		

	// Wrap background_ image around at edge
	// if left edge of background_ > screen left edge
	if (background_.getX() > 0)
		background_.setX(0);

	// if background_ image off screen left
	if (background_.getX() < -MAP_WIDTH + (int)GAME_WIDTH)
		background_.setX(-MAP_WIDTH + (int)GAME_WIDTH);

	// if top edge of background_ > screen top edge
	if (background_.getY() > 0)
		background_.setY(0);

	// if background_ image off screen top
	if (background_.getY() < -MAP_HEIGHT + (int)GAME_HEIGHT)
		background_.setY(-MAP_HEIGHT + (int)GAME_HEIGHT);
	
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
	}
	else if (input->isKeyDown(UP_KEY) || input->getGamepadDPadUp(0))
	{
		if (background_.getY() == -MAP_HEIGHT + (int)GAME_HEIGHT)
		{
			mario_.setState(marioNS::JUMPING);
		}
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

	background_.draw();                     // add the background to the scene
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