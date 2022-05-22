#pragma once
#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenIntro : GameScreen {
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mMenuMario;
	Texture2D* mLevel1Button;
	Texture2D* mLevel2Button;
	Texture2D* mQuitButton;
	bool SetUpLevel();
	float MarioYPos;
	int mOption;
};

#endif // !_GAMESCREENINTRO_H




