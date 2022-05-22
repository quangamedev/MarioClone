#include "GameScreenManager.h"
#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen){
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}
void GameScreenManager::Render() {
	mCurrentScreen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);
}
void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	GameScreenLevel2* tempLevel2Screen;
	GameScreenLevel1* tempLevel1Screen;
	GameScreenIntro* tempIntroScreen;
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}
	switch (newScreen) {
	case SCREEN_LEVEL2:
		tempLevel2Screen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevel2Screen;
		tempLevel2Screen = NULL;
		break;
	case SCREEN_LEVEL1:
		tempLevel1Screen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevel1Screen;
		tempLevel1Screen = NULL;
		break;
	case SCREEN_INTRO:
		tempIntroScreen = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)tempIntroScreen;
		tempIntroScreen = NULL;
		break;
	}
}
GAMESTATE GameScreenManager::GetCurrentGameState() {
	return mCurrentScreen->GetGameState();
}

GAMESTATE GameScreenManager::GetNextGameState() {
	return mCurrentScreen->GetNextGameState();
}
