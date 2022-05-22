#include "CharacterKoopa.h"
#include <iostream>
using namespace std;

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map) {
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	mNumberOfSprites = 2;
	mSingleSpriteWidth = mTexture->GetWidth() / mNumberOfSprites;
	mSingleSpriteHeight = mTexture->GetHeight();
}
CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME_KOOPA;
	Jump();
}

void CharacterKoopa::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightwayUp() {
	mInjured = false;
	Jump();
	if (mFacingDirection == FACING_RIGHT) {
		mFacingDirection = FACING_LEFT;
	}
	else if (mFacingDirection == FACING_LEFT) {
		mFacingDirection = FACING_RIGHT;
	}
}

void CharacterKoopa::Render() {
	//var to hold left pos of spritec (in spritesheet) that will be drawn
	int left = 0;
	//if hurt, use second image on spritesheet
	if (mInjured) {
		left = mSingleSpriteWidth;
	}
	//portion of spritesheet to draw
	SDL_Rect portionOfSpriteSheet = {left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	//where to draw
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else if (mFacingDirection == FACING_LEFT) {
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {

	Character::Update(deltaTime, e);

	//tile y pos of the two pipes on the ground
	if (mPosition.y < 320) {
		if (mMovingLeft && mPosition.x < 0) {
			mFacingDirection = FACING_RIGHT;
		}
		else if (mMovingRight && (mPosition.x + mSingleSpriteWidth) > SCREEN_WIDTH) {
			mFacingDirection = FACING_LEFT;
		}
	}
	if (!mInjured) {
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
			mPosition.x -= KOOPA_SPEED * deltaTime;
		}
		else if (mFacingDirection == FACING_RIGHT) {
			mMovingRight = true;
			mMovingLeft = false;
			mPosition.x += KOOPA_SPEED * deltaTime;
		}
	}
	else {
		//not move while injured
		mMovingRight = false;
		mMovingLeft = false;
		//count down the injured time.
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0) {
			FlipRightwayUp();
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
}
