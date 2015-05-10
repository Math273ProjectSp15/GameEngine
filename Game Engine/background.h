#pragma once
#include "constants.h"

namespace backgroundNS
{
	const int MAP_WIDTH = 3072;
	const int MAP_HEIGHT = 1536;
	const int GRID_LENGTH = 32;
	const int GRID_WIDTH = 96;
	const int GRID_HEIGHT = 48;
	const int GROUND_HEIGHT = 190;
	
	// collision box {left, top, right ,bottom} relative to center
	const RECT GROUND_EDGE = { -12 * 32, -3 * 32, 12 * 32, 3 * 32 };
	const RECT GROUND1_EDGE = { -1.5 * 32, -3 * 32, 1.5 * 32, 3 * 32 };

	const RECT LAVA_EDGE = { -12.5 * 32, -2 * 32, 12.5 * 32, 2 * 32};
	const RECT SPIKE_EDGE = { -10 * 32, -2 * 32, 10 * 32, 2 * 32 };

	const RECT AIRGROUND1_EDGE = { -2.5 * 32, -1.5 * 32, 2.5 * 32, 1.5 * 32};
	const RECT AIRGROUND2_EDGE = { -4 * 32, -1.5 * 32, 4 * 32, 1.5 * 32 };
	const RECT AIRGROUND3_EDGE = { -3 * 32, -1.5 * 32, 3 * 32, 1.5 * 32 };
	
	//Ground Position
	const float GROUND_Y = 42 * 32;
	
	const float GROUND1_X = 0;
	
	const float GROUND2_X = 49 * 32;

	const float GROUND3_X = 93 * 32;

	//Lava Position
	const float LAVA_X = 24 * 32;
	const float LAVA_Y = 44 * 32;

	//Spike Position
	const float SPIKE_X = 73 * 32;
	const float SPIKE_Y = 45 * 32;

	//Air Ground Position
	const float AIRGROUND1_X = 16 * 32;
	const float AIRGROUND1_Y = 32 * 32;

	const float AIRGROUND2_X = 26 * 32;
	const float AIRGROUND2_Y = 26 * 32;

	const float AIRGROUND3_X = 45 * 32;
	const float AIRGROUND3_Y = 25 * 32;

	const float AIRGROUND4_X = 60 * 32;
	const float AIRGROUND4_Y = 25 * 32;

	const float AIRGROUND5_X = 85 * 32;
	const float AIRGROUND5_Y = 15 * 32;

	// G = ground, AG = air ground, L = lava, S = spike
	const int G = 0, AG = 1, L = 2, S = 3;
	// empty tile
	const int __ = -1;                 
}

class Background 
{
public:
	Background();
	
	void update(float X,  float Y);

	//convert the window coordnates to map coordinates 

	float getGroundHeight();
	bool movable(float mapX_, float mapY_, int Height, int width);
private:
	float screenX_;
	float screenY_;

	int level_;
	int grid_[backgroundNS::GRID_WIDTH][backgroundNS::GRID_HEIGHT];
	//(upper left corner coordinate of the screen in the map)
	
	//Enemy enemy_;
	//(There can be many this entities)

};