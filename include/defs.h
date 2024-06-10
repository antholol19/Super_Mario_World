#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Small Mario frame Number
enum MarioState
{
	SMALL_IDLE = 0,
	SMALL_LOOK_UP = 1,
	SMALL_DUCK = 2,
	SMALL_WALK = 3,
	SMALL_RUN = 4
};

struct Vec2D
{
	float x;
	float y;
};

struct Vec2DInt
{
	int x;
	int y;
};

#define MARIO_IMAGE_ARRAY_X 16
#define MARIO_IMAGE_ARRAY_Y 5
#define MARIO_FRAME_WIDTH 48
#define MARIO_FRAME_HEIGHT 48

#define BG_IMAGE_ARRAY_X 4
#define BG_IMAGE_ARRAY_Y 7
#define BG_FRAME_WIDTH 512 
#define BG_FRAME_HEIGHT 432