#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>
#include "online.hpp"

void OnlineGameScene::handleEvents(Game* game) {
	static SDL_Event	event;
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	DIRECTION			oldDirection = board.getDirection(gameInfo->currentPlayer);
	DIRECTION			direction = board.getDirection(gameInfo->currentPlayer);
	Button				*buttonPressed = nullptr;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					direction = DIRECTION::UP;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					direction = DIRECTION::RIGHT;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					direction = DIRECTION::DOWN;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					direction = DIRECTION::LEFT;
					break;
				case SDLK_ESCAPE:
					game->quitGame();
					break;
				default:
					break;
			}
		}
		buttonPressed = handleButtons(game, this, event);
	}
	if (buttonPressed) {
		buttonPressed->onClickEvent(game);
	}
	if (direction != oldDirection) {
		gameInfo->updateClient = true;
		gameInfo->direction = direction;
		gameInfo->updateType = UpdateType::UPDATE_DIRECTION;
	}
}

void OnlineGameScene::initScene(GameWindow& window, void *data) {
	std::cout << "[[OnlineGameScene]]" << std::endl;
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	board.initBoard(window.getRenderer(), gameInfo->nbPlayers, gameInfo->nbPlayers);
}

void OnlineGameScene::updateScene(GameWindow& window, int deltaTime) {
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	// board.updateBoard(window.getRenderer(), gameInfo->currentPlayer);
}

void OnlineGameScene::renderObjects(GameWindow& window) {
	board.render(window.getRenderer());
}