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
	marioWalking.initialize(gamePtr->getGraphics(), marioNS::WALKING_IMAGE_WIDTH, 
		marioNS::WALKING_IMAGE_HEIGHT, marioNS::WALKING_TEXTURE_COLS, textureM);
	marioWalking.setFrames(marioNS::WALKING_MARIO_START_FRAME, marioNS::WALKING_MARIO_END_FRAME);
	marioWalking.setCurrentFrame(marioNS::WALKING_MARIO_START_FRAME);
	marioWalking.setFrameDelay(marioNS::WALKING_ANIMATION_DELAY);

	marioRolling.initialize(gamePtr->getGraphics(), marioNS::ROLLING_IMAGE_WIDTH,
		marioNS::ROLLING_IMAGE_HEIGHT, marioNS::ROLLING_TEXTURE_COLS, textureM);
	marioRolling.setFrames(marioNS::ROLLING_MARIO_START_FRAME, marioNS::ROLLING_MARIO_END_FRAME);
	marioRolling.setCurrentFrame(marioNS::ROLLING_MARIO_START_FRAME);
	marioRolling.setFrameDelay(marioNS::ROLLING_ANIMATION_DELAY);

	marioJumpUp.initialize(gamePtr->getGraphics(), marioNS::JUMP_UP_IMAGE_WIDTH,
		marioNS::JUMP_UP_IMAGE_HEIGHT, marioNS::JUMP_UP_TEXTURE_COLS, textureM);
	marioJumpUp.setFrames(marioNS::JUMP_UP_MARIO_START_FRAME, marioNS::JUMP_UP_MARIO_END_FRAME);
	marioJumpUp.setCurrentFrame(marioNS::JUMP_UP_MARIO_START_FRAME);
	marioJumpUp.setFrameDelay(marioNS::JUMP_UP_ANIMATION_DELAY);

	marioJumpFall.initialize(gamePtr->getGraphics(), marioNS::JUMP_FALL_IMAGE_WIDTH,
		marioNS::JUMP_FALL_IMAGE_HEIGHT, marioNS::JUMP_FALL_TEXTURE_COLS, textureM);
	marioJumpFall.setFrames(marioNS::JUMP_FALL_MARIO_START_FRAME, marioNS::JUMP_FALL_MARIO_END_FRAME);
	marioJumpFall.setCurrentFrame(marioNS::JUMP_FALL_MARIO_START_FRAME);
	marioJumpFall.setFrameDelay(marioNS::JUMP_FALL_ANIMATION_DELAY);

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
		marioWalking.update(frameTime);
		//setFrames(0, 5);
	}
	else if (getState() == marioNS::ROLLING)
	{
		spriteData.y = GAME_HEIGHT - marioNS::ROLLING_IMAGE_HEIGHT;
		if (getDirection() == marioNS::LEFT)
		{
			flipHorizontal(true);
			velocity.x = -abs(marioNS::SPEED);
		}
		else if (getDirection() == marioNS::RIGHT)
		{
			flipHorizontal(false);
			velocity.x = abs(marioNS::SPEED);
		}
		marioRolling.update(frameTime);
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

//=============================================================================
// draw the different mario states
//=============================================================================
void Mario::draw()
{
	if (state_ == marioNS::WALKING)
	{
		marioWalking.draw(spriteData);
	}
	else if (state_ == marioNS::ROLLING)
	{
		marioRolling.draw(spriteData);
	}
	else if (state_ == marioNS::JUMPING)
	{
		if (velocity.y < 0)
			marioJumpUp.draw(spriteData);
		else
			marioJumpFall.draw(spriteData);
	}
	else
	{
		Image::draw();
	}

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