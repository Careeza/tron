#include "networkLogic.h"
#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>
#include "online.hpp"
#include <sstream>

void OnlineGameScene::handleEvents(Game* game) {
	static SDL_Event	event;
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	DIRECTION			direction;
	bool				update = false;
	Button				*buttonPressed = nullptr;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_UP:
				case SDLK_w:
					direction = DIRECTION::UP;
					update = true;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					direction = DIRECTION::RIGHT;
					update = true;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					direction = DIRECTION::DOWN;
					update = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					direction = DIRECTION::LEFT;
					update = true;
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
	if (update) {
		gameInfo->updateClient = true;
		gameInfo->direction = (int)direction;
		gameInfo->updateType = UpdateType::UPDATE_DIRECTION;
	}
}

void OnlineGameScene::initScene(GameWindow& window) {
	std::cout << "[[OnlineGameScene]]" << std::endl;
	background = IMG_LoadTexture(window.getRenderer(), "ressources/game/background.png");
	// gameOnlineInfo *gameInfo = &game->getGameInfo();
	// board.initBoard(window.getRenderer(), gameInfo->nbPlayers, gameInfo->nbPlayers);
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);
	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);
	buttons.push_back(exit);
	music = nullptr;
}

void OnlineGameScene::updateScene(GameWindow& window, int deltaTime) {
	Scene::updateScene(window, deltaTime);
	static bool start = false;
	bool debug = false;

	gameOnlineInfo *gameInfo = &game->getGameInfo();
	if (gameInfo->updateServer) {
		if (gameInfo->updateType == UpdateType::UPDATE_GAME) {
			std::vector<std::string> updates = gameInfo->infoUpdate;
			for (std::string str : updates) {
				if (str[0] == 'S') {
					board.reset();
					unsigned long sendAt = std::stoul(str.substr(2));
					time = sendAt - GETTIMEMS();
					start = true;
				} else if (str[0] == 'P') {
					std::vector<std::string> infos = split(str, '\n');
					int		n = std::stoi(infos[1]);
					std::cout << "n: " << n << std::endl;
					time += GETTIMEMS() - std::stoul(infos[2]);
					std::cout << "time: " << time << std::endl;
					board.updateGameBoard(infos, n);
					debug = true;
				} else if (str[0] == 'D') {
					int n = std::stoi(str.substr(1));
					std::cout << "kill " << n << std::endl;
					board.die(n - 1);
				}
			}
		}
		gameInfo->updateServer = false;
	}

	if (!start) {
		// board.turn();
		return;
	}
	while (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		board.turn();
		board.move(false);
	}
	// if (debug) {
	// 	board.printGameBoard();
	// 	exit(0);
	// }
}

void	OnlineGameScene::giveInfo(void *data) {
	// board.initBoard
	GameWindow& window = game->getWindow();
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	board.initBoard(window.getRenderer(), gameInfo->nbPlayers, gameInfo->currentPlayer - 1);
}


void OnlineGameScene::renderObjects(GameWindow& window) {
	// std::cout << "RENDER" << std::endl;
	board.render(window.getRenderer());
}