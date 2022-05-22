#include "TextRenderer.h"
#include <iostream>
using namespace std;

TextRenderer::TextRenderer(const char* fontPath, int fontSize) {
	font = TTF_OpenFont(fontPath, fontSize);
	color = { 255,255,255,255 };
}
TextRenderer::~TextRenderer() {
	text = NULL;
}
void TextRenderer::Render(SDL_Renderer* renderer, const char* message, int x, int y) {
	//destroys if there is texture
	if (text != NULL) {
		SDL_DestroyTexture(text);
	}
	//craete surface to render
	textSurface = TTF_RenderText_Solid(font, message, color);
	text = SDL_CreateTextureFromSurface(renderer, textSurface);
	//free surface
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	//text position
	textRect.x = x;
	textRect.y = y;
	//render
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, text, NULL, &textRect);
}
void TextRenderer::Render(SDL_Renderer* renderer, int score, int x, int y) {
	char Buffer[256];
	sprintf_s(Buffer, "%i", score);
}