#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H
#include <iostream>
#include "Character.h"
#include <string>

//class CharacterMario : public Character {
//public:
//	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
//	~CharacterMario();
//
//	void Update(float deltaTime, SDL_Event e);
//	
//	
//};
class Character;

class CharacterMario : public Character {
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
};
#endif //_CHARACTERMARIO_H
