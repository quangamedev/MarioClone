#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
//#include <iostream>
#include "Character.h"
#include <string>

class Character;

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);

};
#endif //_CHARACTERLUIGI_H