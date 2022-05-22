#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H
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

class GameScreenLevel2 : GameScreen {
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

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

	void SetLevelMap();
	LevelMap* mLevelMap;
	PowBlock* mPowBlock1;
	PowBlock* mPowBlock2;
	SFXManager* mMusic;

	void DoScreenShake();
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	float mKoopaSpawnTime;
	float mKoopaSpawnTime2;



	std::vector<CharacterKoopa*> mEnemies;
};
#endif // !_GAMESCREENLEVEL2_H



