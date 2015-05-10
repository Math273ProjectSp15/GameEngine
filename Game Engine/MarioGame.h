#pragma once
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Mario.h"
#include "background.h"
#include <vector>

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
	TextureManager backgroundTexture_; // background texture
	TextureManager marioTexture_;     // mario texture
	TextureManager groundTexture_;
	TextureManager ground1Texture_;
	TextureManager lavaTexture_;
	TextureManager spikeTexture_;
	TextureManager airground1Texture_;
	TextureManager airground2Texture_;
	TextureManager airground3Texture_;

	Background Background_;

	Mario mario_;     // mario
	Image background_;// background Image

	std::vector <Entity> ground_;
	std::vector <Entity> airground_;
	Entity lava_;
	Entity spike_;
};

