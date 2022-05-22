#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H
#include <SDL.h>
#include <SDL_image.h>
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Collisions.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D blockPosition);
	~PowBlock();
	void Render();
	Rect2D GetCollisionBox(); /*{ return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }*/
	void TakeAHit(int row);
	bool IsAvailable() { return mNumberOfHitsLeft > 0; }
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	
	int mNumberOfHitsLeft;

};

#endif // !_POWBLOCK_H


