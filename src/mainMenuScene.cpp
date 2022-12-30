#include "game.hpp"
#include "tools.hpp"

void	exitGame(Game *game) {
	game->quitGame();
}

void	playGame(Game *game) {
	game->setScene("singlePlayer");
}

void MainMenuScene::handleEvents(Game* game) {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game->quitGame();
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					game->quitGame();
					break;
				default:
					break;
			}
		}
		if (event.type == SDL_MOUSEMOTION) {
			for (auto& button : buttons) {
				auto [x, y] = game->getWindow().transformPosition(event.motion.x, event.motion.y);
				if (button.isOver(x, y)) {
					button.setOver(true);
				} else {
					button.setOver(false);
				}
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (auto& button : buttons) {
				auto [x, y] = game->getWindow().transformPosition(event.motion.x, event.motion.y);
				if (button.isOver(x, y)) {
					button.onClickEvent(game);
				}
			}
		}
	}
}

void MainMenuScene::initScene(GameWindow& window) {
	background = IMG_LoadTexture(window.getRenderer(), "ressources/background2.png");
	//make the background an SDL_TEXTUREACCESS_TARGET
	Button play(window.getRenderer(), {105, 370, 701, 111}, NULL, playGame);
	play.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	Button multiPlayer(window.getRenderer(), {105, 540, 701, 111}, NULL, playGame);
	multiPlayer.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);
	// Button settings(window.getRenderer(), {105, 715, 701, 111}, NULL);
	// settings.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	buttons.push_back(play);
	buttons.push_back(multiPlayer);
	buttons.push_back(exit);
	// buttons.push_back(settings);
}