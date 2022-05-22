#include <iostream>
#include "GameScreen.h"
using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

GameScreen::~GameScreen() {
	mRenderer = NULL;
}

void GameScreen::Render() {

}

void GameScreen::Update(float deltaTime, SDL_Event e) {

}
void GameScreen::SetGameState(GAMESTATE state) {
	GameState = state;
}
void GameScreen::SetNextGameState(GAMESTATE state) {
	NextGameState = state;
}
