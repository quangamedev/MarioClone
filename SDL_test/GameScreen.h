#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include <iostream>
#include <string>
#include "SDL.h"
#include "Commons.h"


class GameScreen {
protected:
	SDL_Renderer* mRenderer;
	GAMESTATE GameState;
	GAMESTATE NextGameState;
	void SetGameState(GAMESTATE state);
	void SetNextGameState(GAMESTATE state);
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	GAMESTATE GetGameState() { return GameState; }
	GAMESTATE GetNextGameState() { return NextGameState; }
};


#endif