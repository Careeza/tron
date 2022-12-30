#include "game.hpp"
#include "tools.hpp"
#include <iostream>

Button::Button(SDL_Renderer *renderer, SDL_Rect rect_, SDL_Texture *texture_, std::function<void(Game*)> onClick_) : rect(rect_), texture(copyTexture(renderer, texture_)), over(false), overTexture(NULL), onClick(onClick_) {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

Button::~Button() {
	// if (texture) {
	// 	SDL_DestroyTexture(texture);
	// }
	// if (overTexture) {
	// 	SDL_DestroyTexture(overTexture);
	// }
}

void Button::addOverTexture(SDL_Renderer *renderer, SDL_Texture *texture_) {
	overTexture = copyTexture(renderer, texture_);
	SDL_SetTextureBlendMode(overTexture, SDL_BLENDMODE_ADD);
}

void Button::addOverTexture(SDL_Renderer *renderer, std::tuple<int, int, int, int> color) {
	auto [r, g, b, a] = color;
	overTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	SDL_SetTextureBlendMode(overTexture, SDL_BLENDMODE_MUL);
	SDL_SetRenderTarget(renderer, overTexture);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
}

SDL_Texture *Button::getTexture() {
	return (texture);
}

SDL_Texture *Button::getOverTexture() {
	return (overTexture);
}

SDL_Rect& Button::getRect() {
	return (rect);
}

bool Button::isOver(int x, int y) {
	if (x >= rect.x and x <= rect.x + rect.w and y >= rect.y and y <= rect.y + rect.h) {
		over = true;
	} else {
		over = false;
	}
	return (over);
}

void Button::setOver(bool over_) {
	over = over_;
}

bool Button::getOver() {
	return (over);
}

void Button::onClickEvent(Game *game) {
	onClick(game);
}