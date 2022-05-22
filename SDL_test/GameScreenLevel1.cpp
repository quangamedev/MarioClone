#include "GameScreenLevel1.h"
#include <iostream>

using namespace std;

TextRenderer* titleText1;
TextRenderer* returnText1;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	mMusic = new SFXManager();
	mMusic->LoadMusic("Audio/Mario.ogg");
	mMusic->PlayMusic();
}
GameScreenLevel1::~GameScreenLevel1() {
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
	delete mPowBlock;
	mPowBlock = NULL;

	mLevelMap = NULL;
	mKoopaSpawnTime = 2.0f;
	mEnemies.clear();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
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

}
void GameScreenLevel1::Render() {
	//first render object will be on the last layer
	//draw background						wobble
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	titleText1->Render(mRenderer, "Level 1!", SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 4 + 15);
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}
	//draw player
	//myCharacter->Render();
	myMario->Render(false);
	myLuigi->Render(true);
	mPowBlock->Render();
	if (!myMario->GetAlive() || !myLuigi->GetAlive()) {
		returnText1->Render(mRenderer, "Press RETURN to go to Menu", SCREEN_WIDTH / 2 - 160, 352);
	}
	
}
bool GameScreenLevel1::SetUpLevel() {

	SetGameState(GAME_STATE1);
	SetNextGameState(INTRO_STATE);

	titleText1 = new TextRenderer("Fonts/SuperMarioWorld.ttf", 25);
	returnText1 = new TextRenderer("Fonts/SuperMarioWorld.ttf", 15);
	//create the level map
	SetLevelMap();

	//Update the player
	myMario = new CharacterMario(mRenderer, "Images/MarioSprites.png", Vector2D(64, 240), mLevelMap);
	myLuigi = new CharacterLuigi(mRenderer, "Images/LuigiSprites.png", Vector2D(SCREEN_WIDTH-96, 240), mLevelMap);

	//create powblock
	mPowBlock = new PowBlock(mRenderer, mLevelMap, Vector2D((SCREEN_WIDTH * 0.5f) - 32 * 0.5f, 260));
	mScreenShake = false;
	mBackgroundYPos = 0.0f;
	
	//load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!";
		return false;
	}
	else {
		return true;
	}
	
}

void GameScreenLevel1::SetLevelMap() {
	//i stretch the map so that the collision for pow block works normally
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
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

void GameScreenLevel1::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(myMario->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (myMario->IsJumping()) {
				DoScreenShake();
				mPowBlock->TakeAHit(8);
				myMario->CancelJump();
				
			}
		}
	}

	if (Collisions::Instance()->Box(myLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			if (myLuigi->IsJumping()) {
				DoScreenShake();
				mPowBlock->TakeAHit(8);
				myLuigi->CancelJump();
				
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {

	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			//check if enemies is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f) {
				//if enemy is off screen to left/right
				if(mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width*0.5f)
					||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.5f)){
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	myKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);

	mEnemies.push_back(myKoopa);

}

void GameScreenLevel1::SpawnEnemies(float deltaTime) {
	//cout << mKoopaSpawnTime << endl;
	if (mKoopaSpawnTime <= 0) {
		CreateKoopa(Vector2D(160, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(320, 32), FACING_LEFT, KOOPA_SPEED);
		mKoopaSpawnTime = 4.5f;
	}
	else {
		mKoopaSpawnTime -= deltaTime;
	}
}