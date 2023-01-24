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
	DIRECTION			oldDirection = board.getDirection(gameInfo->currentPlayer - 1);
	DIRECTION			direction = board.getDirection(gameInfo->currentPlayer - 1);
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

	gameOnlineInfo *gameInfo = &game->getGameInfo();
	if (gameInfo->updateServer) {
		if (gameInfo->updateType == UpdateType::UPDATE_GAME) {
			std::string	str = gameInfo->gameBoardStr;
			if (str[0] == 'S') {
				unsigned long sendAt = std::stoul(str.substr(2));
				time = sendAt - GETTIMEMS();
				start = true;
			} else {
				std::string		str1;
				int				x;
				int				y;
				unsigned long	sendAt;
				//lis x, y et le temps ou le message a ete recu a partir du 4eme caractere
				std::stringstream ss(str);
				ss >> str1 >> x >> y >> sendAt;
				// time = GETTIMEMS() - sendAt;

				std::cout << "NEW TIME : " << time << std::endl;

				int n = str1[1] - '0' - 1;
				int d = str1[2] - '0';
				std::cout << "n: " << n << " d: " << d << std::endl;
				board.setNextDirection(n, (DIRECTION)d);
				// board.updatePlayer(n, x, y, (DIRECTION)d);
			}
		}
		gameInfo->updateServer = false;
	}

	if (!start) {
		board.turn();
		return;
	}
	while (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		board.turn();
		board.move();
	}
}

void	OnlineGameScene::giveInfo(void *data) {
	// board.initBoard
	GameWindow& window = game->getWindow();
	gameOnlineInfo *gameInfo = &game->getGameInfo();
	board.initBoard(window.getRenderer(), gameInfo->nbPlayers, gameInfo->currentPlayer - 1);
}


void OnlineGameScene::renderObjects(GameWindow& window) {
	board.render(window.getRenderer());
}