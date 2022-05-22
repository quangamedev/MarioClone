#include "Texture2D.h"
#include "Commons.h"
#include <SDL_Image.h>
#include <iostream>
using namespace std;



Texture2D::Texture2D(SDL_Renderer* renderer) {

	mRenderer = renderer;
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D() {
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path) {
	Free();
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL) {
		//set color key
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		//set dimensions
		mWidth = pSurface->w;
		mHeight = pSurface->h;
		//create texture
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL) {
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(pSurface);
	}
	else {
		cout << "Unable to create texture from the surface. Error: " << IMG_GetError() << endl;
	}
	return mTexture != NULL;
}

void Texture2D::Free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) {
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x,newPosition.y,mWidth,mHeight };
	//Render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
	//SDL_RenderPresent(mRenderer);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle) {
	//Render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}
//int Texture2D::GetWidth() {
//	//return mWidth;
//}
//
//int Texture2D::GetHeight() {
//	//return mHeight;
//}
