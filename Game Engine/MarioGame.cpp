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
	// textures
	// background_ texture
	if (!backgroundTexture_.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background_ texture"));

	// mario_ texture
	if (!marioTexture_.initialize(graphics, DARK_MARIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario_ texture"));

	if (!groundTexture_.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground_ texture"));

	if (!ground1Texture_.initialize(graphics, GROUND1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground1_ texture"));

	if (!lavaTexture_.initialize(graphics, LAVA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lava_ texture"));

	if (!spikeTexture_.initialize(graphics, SPIKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spike_ texture"));

	if (!airground1Texture_.initialize(graphics, AIR_GROUND1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground1_ texture"));

	if (!airground2Texture_.initialize(graphics, AIR_GROUND2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground2_ texture"));

	if (!airground3Texture_.initialize(graphics, AIR_GROUND3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airgound3_ texture"));

	// objects
	// background_
	if (!background_.initialize(graphics, 0, 0, 0, &backgroundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	background_.setY((float)GAME_HEIGHT - (float)MAP_HEIGHT);
	//background_.setVisible(false);


	// mario_
	if (!mario_.initialize(this, marioNS::WIDTH, marioNS::HEIGHT, marioNS::TEXTURE_COLS, &marioTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mario texture"));
	mario_.setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
	mario_.setCurrentFrame(marioNS::IDLE_MARIO_START_FRAME);
	mario_.setY((float)GAME_HEIGHT - GROUND_HEIGHT - marioNS::HEIGHT - 30.0);

	//initialize ground
	ground_.resize(3);
	if (!ground_[0].initialize(this, 0, 0, 0, &groundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground0 texture"));
	ground_[0].setCollisionType(entityNS::ROTATED_BOX);
	ground_[0].setEdge(backgroundNS::GROUND1_EDGE);
	// Set position
	ground_[0].setX(backgroundNS::GROUND1_X);
	ground_[0].setY(backgroundNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!ground_[1].initialize(this, 0, 0, 0, &groundTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground1 texture"));
	ground_[1].setCollisionType(entityNS::ROTATED_BOX);
	ground_[1].setEdge(backgroundNS::GROUND1_EDGE);
	// Set position
	ground_[1].setX(backgroundNS::GROUND2_X);
	ground_[1].setY(backgroundNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!ground_[2].initialize(this, 0, 0, 0, &ground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground2 texture"));
	ground_[2].setCollisionType(entityNS::ROTATED_BOX);
	ground_[2].setEdge(backgroundNS::GROUND1_EDGE);
	// Set position
	ground_[2].setX(backgroundNS::GROUND3_X);
	ground_[2].setY(backgroundNS::GROUND_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	//initialize lava
	if (!lava_.initialize(this, 0, 0, 0, &lavaTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing lava texture"));
	lava_.setCollisionType(entityNS::ROTATED_BOX);
	lava_.setEdge(backgroundNS::LAVA_EDGE);
	// Set position
	lava_.setX(backgroundNS::LAVA_X);
	lava_.setY(backgroundNS::LAVA_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	//initialize spike
	if (!spike_.initialize(this, 0, 0, 0, &spikeTexture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spike texture"));
	spike_.setCollisionType(entityNS::ROTATED_BOX);
	spike_.setEdge(backgroundNS::SPIKE_EDGE);
	// Set position
	spike_.setX(backgroundNS::SPIKE_X);
	spike_.setY(backgroundNS::SPIKE_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	//initialize airground
	airground_.resize(5);
	if (!airground_[0].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground0 texture"));
	airground_[0].setCollisionType(entityNS::ROTATED_BOX);
	airground_[0].setEdge(backgroundNS::AIRGROUND1_EDGE);
	// Set position
	airground_[0].setX(backgroundNS::AIRGROUND1_X);
	airground_[0].setY(backgroundNS::AIRGROUND1_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);


	if (!airground_[1].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground1 texture"));
	airground_[1].setCollisionType(entityNS::ROTATED_BOX);
	airground_[1].setEdge(backgroundNS::AIRGROUND1_EDGE);
	// Set position
	airground_[1].setX(backgroundNS::AIRGROUND2_X);
	airground_[1].setY(backgroundNS::AIRGROUND2_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!airground_[2].initialize(this, 0, 0, 0, &airground2Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground2 texture"));
	airground_[2].setCollisionType(entityNS::ROTATED_BOX);
	airground_[2].setEdge(backgroundNS::AIRGROUND2_EDGE);
	// Set position
	airground_[2].setX(backgroundNS::AIRGROUND3_X);
	airground_[2].setY(backgroundNS::AIRGROUND3_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!airground_[3].initialize(this, 0, 0, 0, &airground3Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground3 texture"));
	airground_[3].setCollisionType(entityNS::ROTATED_BOX);
	airground_[3].setEdge(backgroundNS::AIRGROUND3_EDGE);
	// Set position
	airground_[3].setX(backgroundNS::AIRGROUND4_X);
	airground_[3].setY(backgroundNS::AIRGROUND4_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);

	if (!airground_[4].initialize(this, 0, 0, 0, &airground1Texture_))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing airground4 texture"));
	airground_[4].setCollisionType(entityNS::ROTATED_BOX);
	airground_[4].setEdge(backgroundNS::AIRGROUND1_EDGE);
	// Set position
	airground_[4].setX(backgroundNS::AIRGROUND5_X);
	airground_[4].setY(backgroundNS::AIRGROUND5_Y + (float)GAME_HEIGHT - (float)MAP_HEIGHT);
	return;
}

void MarioGame::update()      // must override pure virtual from Game
{
	mario_.update(frameTime);
	for (int i = 0; i < ground_.size(); i++)
	{
		ground_[i].update(frameTime);
	}

	for (int i = 0; i < airground_.size(); i++)
	{
		airground_[i].update(frameTime);
	}

	lava_.update(frameTime);
	spike_.update(frameTime);


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
	


	//Move the background 
	//move the background in X direction opposite mario
	background_.setX(background_.getX() - frameTime * mario_.getVelocity().x);
	for (int i = 0; i < ground_.size(); i++)
	{
		ground_[i].setX(ground_[i].getX() - frameTime * mario_.getVelocity().x);
	}

	for (int i = 0; i < airground_.size(); i++)
	{
		airground_[i].setX(airground_[i].getX() - frameTime * mario_.getVelocity().x);
	}

	lava_.setX(lava_.getX() - frameTime * mario_.getVelocity().x);
	spike_.setX(spike_.getX() - frameTime * mario_.getVelocity().x);
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
	VECTOR2 collisionVector;
	
	for (int i = 0; i < ground_.size(); i++)
	{
		if (mario_.collidesWith(ground_[i], collisionVector))
		{
			mario_.bounce(collisionVector, ground_[i]);
		}
	}
	
	for (int i = 0; i < airground_.size(); i++)
	{
		if (mario_.collidesWith(airground_[i], collisionVector))
		{
			mario_.bounce(collisionVector, airground_[i]);
		}
	}

	if (mario_.collidesWith(lava_, collisionVector))
	{
		mario_.bounce(collisionVector, lava_);
	}

	if (mario_.collidesWith(spike_, collisionVector))
	{
		mario_.bounce(collisionVector, spike_);
	}

}

void MarioGame :: render()      // "
{
	graphics->spriteBegin();                // begin drawing sprites

	for (int i = 0; i < ground_.size(); i++)
	{
		ground_[i].draw();
	}

	for (int i = 0; i < airground_.size(); i++)
	{
		airground_[i].draw();
	}

	lava_.draw();
	spike_.draw();

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