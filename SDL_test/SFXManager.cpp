#include "SFXManager.h"
using namespace std;

SFXManager::SFXManager() {

}
SFXManager::~SFXManager() {
	Mix_FreeChunk(mSound);
	mSound = NULL;
	Mix_FreeMusic(mMusic);
	mMusic = NULL;
}

Mix_Chunk* SFXManager::LoadSoundEffect(std::string soundPath) {
	mSound = Mix_LoadWAV(soundPath.c_str());
	if (mSound == NULL) {
		cout << "Failed to load SFX! Error: " << Mix_GetError() << endl;
	}
	return mSound;
}

void SFXManager::PlaySoundEffect(Mix_Chunk* sound) {
	Mix_PlayChannel(-1, sound, 0);
}

void SFXManager::LoadMusic(std::string musicPath) {
	mMusic = Mix_LoadMUS(musicPath.c_str());
	if (mMusic == NULL) {
		cout << "Failed to load music! Error: " << Mix_GetError() << endl;
	}
}

void SFXManager::PlayMusic(int numberOfLoops) {
	Mix_PlayMusic(mMusic, numberOfLoops);
}
void SFXManager::StopMusic() {
	Mix_HaltMusic();
}