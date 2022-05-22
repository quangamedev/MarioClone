#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
using namespace std;

class GameScreen;

class GameScreenManager {
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	GAMESTATE GetCurrentGameState();
	GAMESTATE GetNextGameState();

	void ChangeScreen(SCREENS newScreen);
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
};
#endif _GAMESCREENMANAGER_H