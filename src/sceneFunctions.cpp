#include "game.hpp"
#include "scene.hpp"
#include <iostream>

void	exitGame(Game *game) {
	game->quitGame();
}

void	playGame(Game *game) {
	std::cout << "play game" << std::endl;
	game->setScene("singlePlayer");
}

void	joinGame(Game *game) {
	std::cout << "join game" << std::endl;
	game->setScene("joinGame");
}

void	returnToMenu(Game *game) {
	std::cout << "return to menu" << std::endl;
	game->setScene("mainMenu");
}

Button	*handleButtons(Game *game, Scene *scene, SDL_Event& event) {
	std::vector<Button>& buttons = scene->getButtons();
	Button *buttonPressed = nullptr;
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
				buttonPressed = &button;
			}
		}
	}
	return buttonPressed;
}