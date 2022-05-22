#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <iostream>
#include <SDL.h>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SFXManager.h"
#include <string>
class Texture2D;
class LevelMap;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render(bool isLuigi);
	virtual void Update(float deltaTime, SDL_Event e);
	void AddGravity(float deltaTime);
	void Jump();
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	bool IsJumping();
	void CancelJump();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	void SetAlive(bool alive);
	bool GetAlive();
	void SetState(CHARACTERSTATE state);
	void Death();
protected:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	bool canMoveLeft;
	bool canMoveRight;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfSprites;
	int mCurrentFrame;
	float mFrameDelay;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	float mCollisionRadius;

	LevelMap* mCurrentLevelMap;

	bool mAlive;
	CHARACTERSTATE mCharacterState;

	SFXManager* mSoundManager;
	Mix_Chunk* mSound;

private:
	
};

#endif // !_CHARACTER_H


