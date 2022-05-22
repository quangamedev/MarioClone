#include "PowBlock.h"
#include <iostream>
#include <string>
using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D blockPosition) {
	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);

	if (!mTexture->LoadFromFile(imagePath.c_str())) {
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;
	mSingleSpriteHeight = mTexture->GetHeight();
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mNumberOfHitsLeft = 3;
	mPosition = blockPosition; //Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

PowBlock::~PowBlock() {
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void PowBlock::TakeAHit(int row) {

	mNumberOfHitsLeft -= 1;
	if (mNumberOfHitsLeft <= 0) {
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(row, 15, 0);
		mLevelMap->ChangeTileAt(row, 16, 0);

	}
}

void PowBlock::Render() {
	if (mNumberOfHitsLeft > 0) {
		//choose sprite to draw
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
		//set sprite area				xPos
		SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		//where to draw
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
		//draw
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
}

Rect2D PowBlock::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}