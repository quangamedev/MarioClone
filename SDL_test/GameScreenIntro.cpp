#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"
#include "Constants.h"
#include "TextRenderer.h"
using namespace std;

TextRenderer* introTitleText;
TextRenderer* introTitleText2;
TextRenderer* copyrightText;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	MarioYPos = 220.0f;
	mOption = 1;
}
GameScreenIntro::~GameScreenIntro() {
	delete mMenuMario;
	mMenuMario = NULL;
	delete mLevel1Button;
	mLevel1Button = NULL;
	delete mLevel2Button;
	mLevel2Button = NULL;
	delete mQuitButton;
	mQuitButton = NULL;
}
void GameScreenIntro::Update(float deltaTime, SDL_Event e) {

	
	//update character

	//spawn enemies
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_w:
			if (mOption > 1)
				mOption--;
			break;
		case SDLK_UP:
			if (mOption > 1)
				mOption--;
			break;
		case SDLK_s:
			if (mOption < 3)
				mOption++;
			break;
		case SDLK_DOWN:
			if (mOption < 3)
				mOption++;
			break;
		default:
			break;
		}
		break;
	}
	switch (mOption) {
	case 1:
		MarioYPos = 220.0f;
		SetNextGameState(GAME_STATE1);
		break;
	case 2:
		MarioYPos = 270.0f;
		SetNextGameState(GAME_STATE2);
		break;
	case 3:
		MarioYPos = 320.0f;
		SetNextGameState(EXIT_STATE);
		break;
	default:
		break;
	}
}
void GameScreenIntro::Render() {

	//draw background						
	//mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	//texture rendering
	mMenuMario->Render(Vector2D(SCREEN_WIDTH / 2 - 110, MarioYPos), SDL_FLIP_NONE);
	mLevel1Button->Render(Vector2D(SCREEN_WIDTH / 2 - 60, 222.0f), SDL_FLIP_NONE);
	mLevel2Button->Render(Vector2D(SCREEN_WIDTH / 2 - 60, 272.0f), SDL_FLIP_NONE);
	mQuitButton->Render(Vector2D(SCREEN_WIDTH / 2 - 60, 322.0f), SDL_FLIP_NONE);
	//text rendering
	introTitleText->Render(mRenderer, "my", SCREEN_WIDTH / 4 - 5, SCREEN_HEIGHT / 4 - 40);
	introTitleText2->Render(mRenderer, "MARIO CLONES.", SCREEN_WIDTH / 4 - 5, SCREEN_HEIGHT / 4 + 10);
	copyrightText->Render(mRenderer, "Recreated by HAN19080023", 14, SCREEN_HEIGHT - 28);
}
bool GameScreenIntro::SetUpLevel() {
	//game state config
	SetGameState(INTRO_STATE);
	SetNextGameState(GAME_STATE1);

	//set font size
	introTitleText = new TextRenderer("Fonts/SuperMarioBros.ttf", 54);
	introTitleText2 = new TextRenderer("Fonts/SuperMarioBros.ttf", 54);
	copyrightText = new TextRenderer("Fonts/SuperMarioWorld.ttf", 14);
	//load the background texture
	//mBackgroundTexture = new Texture2D(mRenderer);
	mMenuMario = new Texture2D(mRenderer);
	mLevel1Button = new Texture2D(mRenderer);
	mLevel2Button = new Texture2D(mRenderer);
	mQuitButton = new Texture2D(mRenderer);
	/*if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!";
		return false;
	}*/
	if (!mMenuMario->LoadFromFile("Images/Mario.png")) {
		cout << "Failed to load Mario texture!";
		return false;
	}
	if (!mLevel1Button->LoadFromFile("Images/ButtonsLevel1.png")) {
		cout << "Failed to load Play button texture!";
		return false;
	}
	if (!mLevel2Button->LoadFromFile("Images/ButtonsLevel2.png")) {
		cout << "Failed to load Play button texture!";
		return false;
	}
	if (!mQuitButton->LoadFromFile("Images/ButtonQuit.png")) {
		cout << "Failed to load Quit button texture!";
		return false;
	}
	else {
		return true;
	}

}








