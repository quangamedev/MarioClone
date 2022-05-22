#include "CharacterMario.h"
#include <iostream>

using namespace std;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {
	mNumberOfSprites = 6;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfSprites;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterMario::~CharacterMario(){

}

void CharacterMario::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_d:
			mMovingRight = false;
			mCurrentFrame = 0;
			break;
		case SDLK_a:
			mMovingLeft = false;
			mCurrentFrame = 0;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_w:
			Jump();

			//mJumping = true;
			break;
		default:
			break;
		}
		break;
	}
	if (GetAlive()) {
		if (mMovingLeft) {
			MoveLeft(deltaTime);
		}
		else if (mMovingRight) {
			MoveRight(deltaTime);
		}
	}
	

	if (mJumping) {
		//ADjust the position
		mPosition.y -= mJumpForce * deltaTime;
		//REduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		//HAs the jump force reduced to 0
		if (mJumpForce <= 0.0f) {
			mJumping = false;
			mCanJump = false;
		}
	}
	SetPosition(mPosition);
	GetPosition();

}
