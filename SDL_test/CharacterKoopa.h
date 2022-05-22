#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"
class Character;
class CharacterKoopa: public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render();
	bool GetInjured() { return mInjured; }
	void Update(float deltaTime, SDL_Event e);
private:

	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	void FlipRightwayUp();
	
	
};
#endif 

