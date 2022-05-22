#include "Character.h"

using namespace std;

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;
	mPosition = startPosition;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mJumpForce = 400.0f;

	mCollisionRadius = 15.0f;
	
	mCurrentLevelMap = map;

	mAlive = true;

	canMoveLeft = true;
	canMoveRight = true;
	
	mSoundManager = new SFXManager();

	
}
Character::~Character() {
	mRenderer = NULL;
}
void Character::Render(bool isLuigi) {
	//top left corner of spritesheet
	//int left = 0;
	int left = mSingleSpriteWidth * mCurrentFrame;
	
	//portion of spritesheet to draw
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	//where to draw
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };


	if (isLuigi) {
		if (mFacingDirection == FACING_RIGHT) {

			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
		}
		else {
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
		}
	}
	else {
		if (mFacingDirection == FACING_RIGHT) {
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
		}
		else {
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
		}
	}
}
void Character::Update(float deltaTime, SDL_Event e) {

	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int centralYPosition = (int)(mPosition.y + mTexture->GetHeight() * 0.5) / TILE_HEIGHT;
	int anklePosition = (int)(mPosition.y + mTexture->GetHeight() * 0.95) / TILE_HEIGHT;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	int headPosition = (int)(mPosition.y) / TILE_HEIGHT;

	if (mMovingLeft == true || mMovingRight == true)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = FRAME_DELAY;

			mCurrentFrame++;

			if (mCurrentFrame > 3)
			{
				mCurrentFrame = 0;
			}
		}
	}
	if (mJumping) {
		mCurrentFrame = 4;
	}
	else if (mCurrentFrame > 3 && mCanJump) {
		mCurrentFrame = 0;
	}

	//left edge
	if (mFacingDirection == FACING_LEFT) {
		if (mCurrentLevelMap->GetTileAt(headPosition, mPosition.x / TILE_WIDTH) == 1) {
			canMoveLeft = false;
		}
		else if (mCurrentLevelMap->GetTileAt(centralYPosition, mPosition.x / TILE_WIDTH) == 1) {
			canMoveLeft = false;
		}
		else if (mCurrentLevelMap->GetTileAt(anklePosition, mPosition.x / TILE_WIDTH) == 1) {
			canMoveLeft = false;
		}
		else {
			canMoveLeft = true;
		}
	}
	else {
		canMoveLeft = true;
	}
	//right edge
	if (mFacingDirection == FACING_RIGHT) {
		if (mCurrentLevelMap->GetTileAt(headPosition, (mPosition.x + mSingleSpriteWidth) / TILE_WIDTH) == 1) {
			canMoveRight = false;
		}
		else if (mCurrentLevelMap->GetTileAt(centralYPosition, (mPosition.x + mSingleSpriteWidth) / TILE_WIDTH) == 1) {
			canMoveRight = false;
		}
		else if (mCurrentLevelMap->GetTileAt(anklePosition, (mPosition.x + mSingleSpriteWidth) / TILE_WIDTH) == 1) {
			canMoveRight = false;
		}
		else {
			canMoveRight = true;
		}
	}
	else {
		canMoveRight = true;
	}
	//head
	if (mCurrentLevelMap->GetTileAt(headPosition, (mPosition.x + 5.0f) / TILE_WIDTH) == 1 || mCurrentLevelMap->GetTileAt(headPosition, (mPosition.x + mSingleSpriteWidth - 5.0f) / TILE_WIDTH) == 1) {
		if(GetAlive())
		mJumping = false;
	}
	if (!GetAlive()) {
		//death
		mCurrentFrame = 5;
		mPosition.y += 360.0f * deltaTime;
		mCanJump = false;
		
	}
	else if (mCurrentLevelMap->GetTileAt(footPosition, (mPosition.x + 5.0f) / TILE_WIDTH) == 0 && mCurrentLevelMap->GetTileAt(footPosition, (mPosition.x + mSingleSpriteWidth - 5.0f) / TILE_WIDTH) == 0) {
		AddGravity(deltaTime);
	}
	else {
		mCanJump = true;
	}
	
}

void Character::MoveLeft(float deltaTime) {
	if (canMoveLeft) {
		mFacingDirection = FACING_LEFT;
		mPosition.x -= MOVEMENT_SPEED * deltaTime;
	}
}

void Character::MoveRight(float deltaTime) {
	if (canMoveRight) {
		mFacingDirection = FACING_RIGHT;
		mPosition.x += MOVEMENT_SPEED * deltaTime;
	}
}
void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {
	return mPosition;
}

void Character::AddGravity(float deltaTime) {
	
	mPosition.y += GRAVITY_FORCE * deltaTime;
	mCanJump = false;
}

void Character::Jump() {
	if (!mJumping && mCanJump) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mSound = mSoundManager->LoadSoundEffect("Audio/Jump.wav");
		mSoundManager->PlaySoundEffect(mSound);
		mJumping = true;
		mCanJump = false;
	}
}

void Character::Death() {
	SetAlive(false);
	mSound = mSoundManager->LoadSoundEffect("Audio/Die.wav");
	mSoundManager->PlaySoundEffect(mSound);
	mJumpForce = INITIAL_JUMP_FORCE;
	mJumping = true;
	mCanJump = false;
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());
}

bool Character::IsJumping() {
	if (mJumping) {
		return true;
	}
	return false;
}

void Character::CancelJump() {
	mJumping = false;
}

void Character::SetState(CHARACTERSTATE state) {
	mCharacterState = state;
}

void Character::SetAlive(bool alive) {
	mAlive = alive;
}

bool Character::GetAlive() {
	return mAlive;
}