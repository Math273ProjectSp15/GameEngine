#include "Mario.h"

Mario::Mario() : Entity()
{
	spriteData.width = marioNS::WIDTH ;         // size of Mario
	spriteData.height = marioNS::HEIGHT;
	spriteData.x = marioNS::X;                 // location on screen
	spriteData.y = marioNS::Y;
	spriteData.rect.bottom = marioNS::HEIGHT;  // rectangle to select parts of an image
	spriteData.rect.right = marioNS::WIDTH;
	frameDelay = 0.1;
	startFrame = 0;                             // first frame of animation
	endFrame = 0;                           // last frame of animation
	currentFrame = startFrame;
	edge.top = -marioNS::HEIGHT / 2 ;             // set collision edges
	edge.bottom = marioNS::HEIGHT / 2 ;
	edge.left = -marioNS::WIDTH / 2 ;
	edge.right = marioNS::WIDTH / 2 ;

	collisionType = entityNS::ROTATED_BOX;
	mass = marioNS::MASS;

	velocity.x = 0;
	velocity.y = 0;

	state_ = marioNS::IDLEING;
	direction_ = marioNS::RIGHT;
}

//=============================================================================
// Initialize Mario.
// Post: returns true if successful, false if failed
//=============================================================================
bool Mario::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	marioRunning.initialize(gamePtr->getGraphics(), marioNS::RUNNING_IMAGE_WIDTH, 
		marioNS::RUNNING_IMAGE_HEIGHT, marioNS::RUNNING_TEXTURE_COLS, textureM);
	marioRunning.setFrames(marioNS::RUNNING_MARIO_START_FRAME, marioNS::RUNNING_MARIO_END_FRAME);
	marioRunning.setCurrentFrame(marioNS::RUNNING_MARIO_START_FRAME);
	//marioRunning.setFrameDelay(marioNS::)
	//engine.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//engine.setFrames(shipNS::ENGINE_START_FRAME, shipNS::ENGINE_END_FRAME);
	//engine.setCurrentFrame(shipNS::ENGINE_START_FRAME);
	//engine.setFrameDelay(shipNS::ENGINE_ANIMATION_DELAY);
	//shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
	//shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
	//shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
	//shield.setLoop(false);                  // do not loop animation
	//explosion.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//explosion.setFrames(shipNS::EXPLOSION_START_FRAME, shipNS::EXPLOSION_END_FRAME);
	//explosion.setCurrentFrame(shipNS::EXPLOSION_START_FRAME);
	//explosion.setFrameDelay(shipNS::EXPLOSION_ANIMATION_DELAY);
	//explosion.setLoop(false);               // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Mario::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;         // move along X 
	spriteData.y += frameTime * velocity.y;         // move along Y

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - marioNS::WIDTH)  // if hit right screen edge
	{
		spriteData.x = 0;  
	} 
	else if (spriteData.x < 0)                       // else if hit left screen edge
	{
		spriteData.x = GAME_WIDTH - marioNS::WIDTH;                   
	}
	else if (spriteData.y > GAME_HEIGHT - marioNS::HEIGHT) // else if below ground
	{
		spriteData.y = GAME_HEIGHT - marioNS::HEIGHT;
	}

	if (getState() == marioNS::IDLEING)
	{
		setFrames(marioNS::IDLE_MARIO_START_FRAME, marioNS::IDLE_MARIO_END_FRAME);
		if (spriteData.y == GAME_HEIGHT - marioNS::HEIGHT)
		{
			velocity.x = 0;
		}
	}
	else if (getState() == marioNS::WALKING)
	{
		if (getDirection() != marioNS::RIGHT)
		{
			flipHorizontal(true);
			velocity.x = -abs(marioNS::SPEED);
		}
		else if (getDirection() == marioNS::RIGHT)
		{
			flipHorizontal(false);
			velocity.x = abs(marioNS::SPEED);
		}
		//marioRunning.update(frameTime);
		//setFrames(0, 5);
	}
	else if (getState() == marioNS::CROUCHING)
	{

	}
	else if (getState() == marioNS::JUMPING)
	{
		if (spriteData.y == GAME_HEIGHT - marioNS::HEIGHT)
		{
			velocity.y = -3 * marioNS::SPEED;
		}
	}

	velocity.y += frameTime * 3 * GRAVITY;
	
}

void Mario::setState(marioNS::State state)
{
	state_ = state;
}

marioNS::State Mario::getState()
{
	return state_;
}

void Mario::setDirection(marioNS::Direction direction)
{
	direction_ = direction;
}

marioNS::Direction Mario::getDirection()
{
	return direction_;
}