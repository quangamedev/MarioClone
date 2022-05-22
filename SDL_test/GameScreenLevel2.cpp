#include "GameScreenLevel2.h"
#include <iostream>

using namespace std;

TextRenderer* titleText2;
TextRenderer* returnText2;

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	mMusic = new SFXManager();
	mMusic->LoadMusic("Audio/MarioUnderworld.ogg");
	mMusic->PlayMusic();
}
GameScreenLevel2::~GameScreenLevel2() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
	delete myMario;
	myMario = NULL;
	delete myLuigi;
	myLuigi = NULL;
	delete myKoopa;
	myKoopa = NULL;
	delete mPowBlock1;
	mPowBlock1 = NULL;
	delete mPowBlock2;
	mPowBlock2 = NULL;

	mLevelMap = NULL;
	mKoopaSpawnTime = 1.5f;
	mKoopaSpawnTime2 = 2.0f;
	mEnemies.clear();
}
void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {
	//do the screenshake when prompted
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//end screenshake after screenshake duration
		if (mScreenShakeTime <= 0.0f) {
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	if (myMario->GetAlive() && myLuigi->GetAlive()) {
		myMario->Update(deltaTime, e);
		myLuigi->Update(deltaTime, e);
		UpdatePOWBlock();

		//spawn enemies
		SpawnEnemies(deltaTime);
		UpdateEnemies(deltaTime, e);
	}
	else if (!myMario->GetAlive()) {
		myMario->Update(deltaTime, e);
	}
	else if (!myLuigi->GetAlive()) {
		myLuigi->Update(deltaTime, e);
	}
	//update character


	//if circle collision happens
	//if (Collisions::Instance()->Circle(myMario, myLuigi)) {
	//	//cout << "yes" << endl;
	//}

	//if box collision happens
}
void GameScreenLevel2::Render() {
	//first render object will be on the last layer
	//draw background						wobble
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	titleText2->Render(mRenderer, "Level 2!", SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 4 + 15);

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
	//draw player
	//myCharacter->Render();
	myMario->Render(false);
	myLuigi->Render(true);
	mPowBlock1->Render();
	mPowBlock2->Render();

	if (!myMario->GetAlive() || !myLuigi->GetAlive()) {
		returnText2->Render(mRenderer, "Press RETURN to go to Menu", SCREEN_WIDTH / 2 - 160, 352);
	}
}
bool GameScreenLevel2::SetUpLevel() {

	SetGameState(GAME_STATE1);
	SetNextGameState(INTRO_STATE);

	titleText2 = new TextRenderer("Fonts/SuperMarioWorld.ttf", 25);
	returnText2 = new TextRenderer("Fonts/SuperMarioWorld.ttf", 15);

	//create the level map
	SetLevelMap();

	//Update the player
	myMario = new CharacterMario(mRenderer, "Images/MarioSprites.png", Vector2D(96, 288), mLevelMap);
	myLuigi = new CharacterLuigi(mRenderer, "Images/LuigiSprites.png", Vector2D(SCREEN_WIDTH - 128, 288), mLevelMap);

	//create powblock
	mPowBlock1 = new PowBlock(mRenderer, mLevelMap, Vector2D((SCREEN_WIDTH * 0.5f) - 32 * 0.5f, 64));
	mPowBlock2 = new PowBlock(mRenderer, mLevelMap, Vector2D((SCREEN_WIDTH * 0.5f) - 32 * 0.5f, 188));
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level2.png")) {
		cout << "Failed to load background texture!";
		return false;
	}
	else {
		return true;
	}

}

void GameScreenLevel2::SetLevelMap() {
	//i stretch the map so that the collision for pow block works normally
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,2,2,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	//clear any old maps
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}
	//set up a new one
	mLevelMap = new LevelMap(map);

}

void GameScreenLevel2::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(myMario->GetCollisionBox(), mPowBlock1->GetCollisionBox())) {
		if (mPowBlock1->IsAvailable()) {
			if (myMario->IsJumping()) {
				DoScreenShake();
				mPowBlock1->TakeAHit(2);
				myMario->CancelJump();
				cout << "bnruh" << endl;
			}
		}
	}

	if (Collisions::Instance()->Box(myLuigi->GetCollisionBox(), mPowBlock1->GetCollisionBox())) {
		if (mPowBlock1->IsAvailable()) {
			if (myLuigi->IsJumping()) {
				DoScreenShake();
				mPowBlock1->TakeAHit(2);
				myLuigi->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(myMario->GetCollisionBox(), mPowBlock2->GetCollisionBox())) {
		if (mPowBlock2->IsAvailable()) {
			if (myMario->IsJumping()) {
				DoScreenShake();
				mPowBlock2->TakeAHit(6);
				myMario->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(myLuigi->GetCollisionBox(), mPowBlock2->GetCollisionBox())) {
		if (mPowBlock2->IsAvailable()) {
			if (myLuigi->IsJumping()) {
				DoScreenShake();
				mPowBlock2->TakeAHit(6);
				myLuigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel2::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e) {

	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			//check if enemies is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f) {
				//if enemy is off screen to left/right
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f)
					||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.5f)) {
					mEnemies[i]->SetAlive(false);
				}
			}
			mEnemies[i]->Update(deltaTime, e);
			
				
			if (Collisions::Instance()->Circle(mEnemies[i], myMario)) {
					
				if (mEnemies[i]->GetInjured()) {
					mEnemies[i]->SetAlive(false);
				}
				else if (myMario->GetAlive()) {
					myMario->SetState(CHARACTERSTATE_PLAYER_DEATH);
					myMario->Death();
					mMusic->StopMusic();
				}
			}
			else if (Collisions::Instance()->Circle(mEnemies[i], myLuigi)) {
				if (mEnemies[i]->GetInjured()) {
					mEnemies[i]->SetAlive(false);
				}
				else if (myMario->GetAlive()) {
					myLuigi->SetState(CHARACTERSTATE_PLAYER_DEATH);
					myLuigi->Death();
					mMusic->StopMusic();
				}
			}
			
			//delete enemy if it is dead
			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1) {
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed) {
	myKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);

	mEnemies.push_back(myKoopa);

}

void GameScreenLevel2::SpawnEnemies(float deltaTime) {
	//cout << mKoopaSpawnTime << endl;
	if (mKoopaSpawnTime <= 0) {
		CreateKoopa(Vector2D(32, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(448, 32), FACING_LEFT, KOOPA_SPEED);
		mKoopaSpawnTime = 5.0f;
	}
	else {
		mKoopaSpawnTime -= deltaTime;
	}
	if (mKoopaSpawnTime2 <= 0) {
		CreateKoopa(Vector2D(160, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(320, 32), FACING_LEFT, KOOPA_SPEED);
		mKoopaSpawnTime2 = 8.0f;
	}
	else {
		mKoopaSpawnTime2 -= deltaTime;
	}
}
