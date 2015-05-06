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
	background_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);

	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));
	
	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);
	mario_.setY((float)GAME_HEIGHT - GROUND_HEIGHT - marioNS::HEIGHT - 30.0);
	return;
}

void MarioGame::update()      // must override pure virtual from Game
{
	if (input->isKeyDown(LEFT_KEY) || input->getGamepadDPadLeft(0))
	{
		mario_.setDirection(marioNS::LEFT);
		mario_.setState(marioNS::WALKING);
		if (input->isKeyDown(UP_KEY))
		{
			mario_.setState(marioNS::JUMPING);
		}
	}
	else if (input->isKeyDown(RIGHT_KEY) && !input->isKeyDown(DOWN_KEY) || input->getGamepadDPadRight(0))
	{
		mario_.setDirection(marioNS::RIGHT);
		mario_.setState(marioNS::WALKING);
		if (input->isKeyDown(UP_KEY))
		{	
			mario_.setState(marioNS::JUMPING);
		}
	}
	else if (input->isKeyDown(DOWN_KEY) || input->getGamepadDPadDown(0))
	{
		mario_.setState(marioNS::ROLLING);
	}
	else if (input->isKeyDown(UP_KEY) || input->getGamepadDPadUp(0))
	{
		mario_.setState(marioNS::JUMPING);
	}
	else
	{
		mario_.setState(marioNS::IDLEING);
	}
	mario_.update(frameTime, &Background_);

	//Move the background 
	// move the background in X direction opposite mario
	background_.setX(background_.getX() - frameTime * mario_.getVelocity().x);
	//Wrap Backround
	//if (background_.getX() > 0)
	//	background_.setX(background_.getX() - backgroundNS::MAP_WIDTH);
	//if (background_.getX() < -backgroundNS::MAP_WIDTH)
	//	background_.setX(background_.getX() + backgroundNS::MAP_WIDTH);
	// move background in Y direction opposite mario
	//background_.setY(background_.getY() - frameTime * mario_.getVelocity().y);

	
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