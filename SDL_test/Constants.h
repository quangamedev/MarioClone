#pragma once

//screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

//characters' metrics
#define GRAVITY_FORCE 180.0f
#define MOVEMENT_SPEED 120.0f
#define JUMP_FORCE_DECREMENT 1250.0f
#define INITIAL_JUMP_FORCE 760.0f
#define FRAME_DELAY 0.1

//Map size, stretched width (less tile width, more tiles), height remains the same
#define MAP_HEIGHT 13
#define MAP_WIDTH 32
#define TILE_HEIGHT 32
#define TILE_WIDTH 16

//powblock screen shake
#define SCREENSHAKE_DURATION 0.25f

//koopa
#define INJURED_TIME_KOOPA 3.5f
#define KOOPA_SPEED 48.0f
#define INITIAL_JUMP_FORCE_SMALL 450.0f