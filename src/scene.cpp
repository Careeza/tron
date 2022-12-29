#include "game.hpp"
#include <iostream>

Scene::Scene() : time(0) {}
Scene::~Scene() {
	SDL_DestroyTexture(background);
}

void			Scene::renderScene(GameWindow& window) {
	SDL_SetRenderTarget(window.getRenderer(), window.getVirtualWindow());

	SDL_RenderCopy(window.getRenderer(), background, NULL, NULL);
	for (auto button : buttons) {
		if (button.getTexture()) {
			SDL_RenderCopy(window.getRenderer(), button.getTexture(), NULL, &button.getRect());
		}
		if (button.getOverTexture() and button.getOver()) {
			SDL_RenderCopy(window.getRenderer(), button.getOverTexture(), NULL, &button.getRect());
		}
	}
	SDL_SetTextureBlendMode(window.getVirtualWindow(), SDL_BLENDMODE_BLEND);
	renderGameObjects(window);
}
