#pragma once
#ifndef _SFXMANAGER_H_
#define _SFXMANAGER_H_
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
class SFXManager
{
public:
	SFXManager();
	~SFXManager();

	Mix_Chunk* LoadSoundEffect(std::string soundPath);
	void PlaySoundEffect(Mix_Chunk* sound);

	void LoadMusic(std::string musicPath);
	void PlayMusic(int numberOfLoops = -1);
	void StopMusic();
private:
	Mix_Chunk* mSound;
	Mix_Music* mMusic;
};
#endif // !_SFXMANAGER_H_


