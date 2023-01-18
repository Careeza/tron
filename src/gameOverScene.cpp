#include "scene.hpp"
#include "game.hpp"

void	GameOverScene::handleEvents(Game *game) {
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->quitGame();
		}
	}
}

void	GameOverScene::initScene(GameWindow& window, void *data) {
	score = *(int *)data;
	delete (int *)data;
	//take a screenshot of the game
	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, window.getWidth(), window.getHeight(), 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_RenderReadPixels(window.getRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
	background = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
	SDL_FreeSurface(surface);
	gameOverTexture = IMG_LoadTexture(window.getRenderer(), "ressources/gameOver.png");
	skullAnimation.init(window.getRenderer(), "ressources/skullAnimation.png", 11, 120, 12);
}

void	GameOverScene::renderObjects(GameWindow& window) {
	SDL_RenderCopy(window.getRenderer(), gameOverTexture, NULL, NULL);
	skullAnimation.render({845, 424, 230, 230});
	window.drawNumber(score, 1235, 800, 2);
}

void	GameOverScene::updateScene(GameWindow& window, int deltaTime) {
	skullAnimation.update(deltaTime);
}

void	GameOverScene::deleteScene() {
	// Scene::deleteScene();
}