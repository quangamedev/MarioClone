#pragma once
#ifndef _COMMONS_H
#define _COMMONS_H
struct Vector2D {
	float x;
	float y;
	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float X, float Y) {
		x = X;
		y = Y;
	}
};

struct Rect2D {
	float x;
	float y;
	float width;
	float height;
	Rect2D() {
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	Rect2D(float X, float Y, float Width, float Height) {
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}
};

enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING {
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTERSTATE {
	CHARACTERSTATE_PLAYER_DEATH
};
enum GAMESTATE {
	EXIT_STATE = 0,
	INTRO_STATE,
	GAME_STATE1,
	GAME_STATE2
};
#endif