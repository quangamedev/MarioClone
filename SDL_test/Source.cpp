#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <string>

using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//SDL_Texture* gTexture = NULL;
//Texture2D* gTexture = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void LoadMusic(string path);
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
//void FreeTexture();

int main(int argc, char* args[]) {
	//check if we want to quit
	

	if (InitSDL()) {
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
		bool quit = false;
		//Game loop
		while (!quit) {
			Render();
			quit = Update();
		}
		return true;
		
		gOldTime = SDL_GetTicks();
	}
	//Close Window and save resources
	
	CloseSDL();
	return 0;
}

bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else {
		//All good, try to create window
		gWindow = SDL_CreateWindow("super MARIO CLONE by HAN19080023",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (gWindow == NULL) { //Did window get created
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}

	
	//initialise renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	//allow PNG loading
	if(gRenderer != NULL) {
		int imageFlags = IMG_INIT_PNG;
		//not being able to set PNG type
		if (!(IMG_Init(imageFlags) & imageFlags)) {
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
		
	}
	//render equals NULL
	else {
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}
	
	//initialise mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;
		return false;
	}

	if (TTF_Init() < 0) {
		cout << "Error: " << TTF_GetError() << endl;
		return false;
	}
	return true;
}

void Render() {
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//render screen
	gameScreenManager->Render();
	

	//update the screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path) {
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL) {
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}

}


void CloseSDL() {
	//Clear up texture
	//FreeTexture();
	//delete gTexture;
	//gTexture = NULL;
	delete gameScreenManager;
	gameScreenManager = NULL;
	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	//Quit SDL subsystem
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Update() {
	Uint32 newTime = SDL_GetTicks();
	//Event handler
	SDL_Event e;
	//Get the events
	SDL_PollEvent(&e);
	//Handle any events
	
	switch (e.type) {
		//Click 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
			if (gameScreenManager->GetNextGameState() == GAME_STATE1) {
				gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
			}
			else if (gameScreenManager->GetNextGameState() == GAME_STATE2) {
				gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
			}
			else if (gameScreenManager->GetCurrentGameState() == GAME_STATE1) {
				gameScreenManager->ChangeScreen(SCREEN_INTRO);
			}
			else if (gameScreenManager->GetNextGameState() == EXIT_STATE) {
				return true;
			}
			break;
		default:
			break;
		}

	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	//cout << "" << endl;
	return false;
	
}
