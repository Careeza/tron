#include "scene.hpp"
#include "game.hpp"
#include <fstream>

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

void	GameOverScene::initScene(GameWindow& window) {
	// SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, window.getWidth(), window.getHeight(), 32, SDL_PIXELFORMAT_ARGB8888);
	// SDL_RenderReadPixels(window.getRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
	// background = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
	// SDL_FreeSurface(surface);
	background = IMG_LoadTexture(window.getRenderer(), "ressources/game/background.png");
	gameOverTexture = IMG_LoadTexture(window.getRenderer(), "ressources/gameover/V2/gameOver.png");
	skullAnimation.init(window.getRenderer(), "ressources/gameover/V2/skullAnimation.png", 11, 120, 12);
	bestScoreAnimation.init(window.getRenderer(), "ressources/gameover/V2/bestScoreAnimation.png", 5, 120, 12);

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

void	GameOverScene::giveInfo(void *data) {
	score = *(int *)data;
	delete (int *)data;

	std::ifstream file("ressources/bestScore.txt");
	if (!file.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	file.close();
	int	bestScore = std::stoi(line);
	if (score > bestScore) {
		bestScore = score;
		std::ofstream file("ressources/bestScore.txt");
		if (!file.is_open()) {
			std::cout << "Error opening file" << std::endl;
			return;
		}
		file << bestScore;
		file.close();
		bestScoreBeat = true;
	} else {
		bestScoreBeat = false;
	}
}

void	GameOverScene::renderObjects(GameWindow& window) {
	SDL_RenderCopy(window.getRenderer(), gameOverTexture, NULL, NULL);
	skullAnimation.render({840, 284, 230, 230});
	if (bestScoreBeat) {
		bestScoreAnimation.render({772, 718, 466, 158});
	}
	window.drawNumber(score, 1070, 647, 2, DRAW_MODE::LEFT);
}

void	GameOverScene::updateScene(GameWindow& window, int deltaTime) {
	skullAnimation.update(deltaTime);
	if (bestScoreBeat) {
		bestScoreAnimation.update(deltaTime);
	}
}

void	GameOverScene::deleteScene() {
	// Scene::deleteScene();
}