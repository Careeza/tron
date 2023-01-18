#include "game.hpp"
#include <iostream>

Scene::~Scene() {
	deleteScene();
}

void			Scene::renderScene(GameWindow& window) {
	SDL_SetRenderTarget(window.getRenderer(), window.getVirtualWindow());

	SDL_RenderCopy(window.getRenderer(), background, NULL, NULL);
	renderObjects(window);
	for (auto button : buttons) {
		if (button.getTexture()) {
			SDL_RenderCopy(window.getRenderer(), button.getTexture(), NULL, &button.getRect());
		}
		if (button.getOverTexture() and button.getOver()) {
			SDL_RenderCopy(window.getRenderer(), button.getOverTexture(), NULL, &button.getRect());
		}
	}
	SDL_SetTextureBlendMode(window.getVirtualWindow(), SDL_BLENDMODE_BLEND);
}

void			Scene::playMusic() {
	if (music) {
		Mix_PlayMusic(music, -1);
	}
}

void			Scene::stopMusic() {
	if (music) {
		Mix_HaltMusic();
	}
}

void			Scene::deleteScene() {
	SDL_DestroyTexture(background);
	for (auto button : buttons) {
		if (button.getTexture()) {
			SDL_DestroyTexture(button.getTexture());
		}
		if (button.getOverTexture()) {
			SDL_DestroyTexture(button.getOverTexture());
		}
	}
	Mix_FreeMusic(music);
}