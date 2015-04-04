#pragma once
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Mario.h"

class MarioGame : public Game
{
public:
	// Constructor
	MarioGame();
	// Destructor
	virtual ~MarioGame();
	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

//=============================================================================
// This class is the core of the game
//=============================================================================
private:
	// game items
	TextureManager backgroundTexture_; // backdrop texture
	TextureManager marioTexture_;     // ball texture
	
	Mario mario_; // mario
	Image background_;// background
};

