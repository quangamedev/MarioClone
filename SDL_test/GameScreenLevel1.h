#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <SDL.h>
#include <vector>
#include "Commons.h"
#include "Texture2D.h"
#include "Constants.h"
#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Character.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "TextRenderer.h"
#include "SFXManager.h"

class Character;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;

class Texture2D;
class Collisions;
class PowBlock;

class GameScreenLevel1 : GameScreen {
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void SpawnEnemies(float deltaTime);
private:
	
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	CharacterMario* myMario;
	CharacterLuigi* myLuigi;
	CharacterKoopa* myKoopa;
	Character* myCharacter;
	SFXManager* mMusic;

	void SetLevelMap();
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	void DoScreenShake();
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	float mKoopaSpawnTime;

	std::vector<CharacterKoopa*> mEnemies;
};

#endif