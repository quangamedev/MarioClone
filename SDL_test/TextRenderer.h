#pragma once
#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

class TextRenderer
{
public:
	TextRenderer(const char* fontPath, int fontSize);
	~TextRenderer();
	void Render(SDL_Renderer* renderer, const char* message, int x, int y);
	void Render(SDL_Renderer* renderer, int score, int x, int y);
private:
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect textRect;
};

#endif // !_TEXTRENDERER_H



