#include "scene.hpp"
#include "game.hpp"

void	GameOverScene::handleEvents(Game *game) {
	SDL_Event 	event;
	Button		*buttonPressed = nullptr;
	
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->quitGame();
		}
		buttonPressed = handleButtons(game, this, event);
	}
	if (buttonPressed) {
		buttonPressed->onClickEvent(game);
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
	gameOverTexture = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/gameOver.png");
	skullAnimation.init(window.getRenderer(), "ressources/gameover/V2/skullAnimation.png", 11, 120, 12);

	SDL_Texture *returnButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/btn_nhover_return.png");
	SDL_Texture *returnButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/btn_hover_return.png");
	Button returnButton(window.getRenderer(), {395, 877, 525, 112}, returnButtonOff, returnToMenu);
	returnButton.addOverTexture(window.getRenderer(), returnButtonOn);

	SDL_DestroyTexture(returnButtonOff);
	SDL_DestroyTexture(returnButtonOn);

	buttons.push_back(returnButton);

	SDL_Texture *playAgainButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/btn_nhover_again.png");
	SDL_Texture *playAgainButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/btn_hover_again.png");
	Button playAgainButton(window.getRenderer(), {1010, 877, 525, 112}, playAgainButtonOff, playGame);
	playAgainButton.addOverTexture(window.getRenderer(), playAgainButtonOn);

	SDL_DestroyTexture(playAgainButtonOff);
	SDL_DestroyTexture(playAgainButtonOn);

	buttons.push_back(playAgainButton);
}

void	GameOverScene::renderObjects(GameWindow& window) {
	SDL_RenderCopy(window.getRenderer(), gameOverTexture, NULL, NULL);
	skullAnimation.render({840, 284, 230, 230});
	window.drawNumber(score, 1235, 800, 2);
}

void	GameOverScene::updateScene(GameWindow& window, int deltaTime) {
	skullAnimation.update(deltaTime);
}

void	GameOverScene::deleteScene() {
	// Scene::deleteScene();
}