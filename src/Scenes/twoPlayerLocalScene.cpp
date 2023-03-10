#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>
#include "online.hpp"

void TwoPlayerLocalScene::handleEvents(Game* game) {
	static SDL_Event	event;
	DIRECTION			directionP1 = board.getDirection(0);
	DIRECTION			directionP2 = board.getDirection(1);
	Button				*buttonPressed = nullptr;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_UP:
					directionP2 = DIRECTION::UP;
					break;
				case SDLK_w:
					directionP1 = DIRECTION::UP;
					break;
				case SDLK_RIGHT:
					directionP2 = DIRECTION::RIGHT;
					break;
				case SDLK_d:
					directionP1 = DIRECTION::RIGHT;
					break;
				case SDLK_DOWN:
					directionP2 = DIRECTION::DOWN;
					break;
				case SDLK_s:
					directionP1 = DIRECTION::DOWN;
					break;
				case SDLK_LEFT:
					directionP2 = DIRECTION::LEFT;
					break;
				case SDLK_a:
					directionP1 = DIRECTION::LEFT;
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
	board.setNextDirection(0, directionP1);
	board.setNextDirection(1, directionP2);
}

void TwoPlayerLocalScene::initScene(GameWindow& window) {
	std::cout << "[[TwoPlayerLocalScene]]" << std::endl;
	board.initBoard(window.getRenderer(), 2, -1);
	crownP1 = IMG_LoadTexture(window.getRenderer(), "ressources/twoPlayerLocal/blue_crown.png");
	crownP2 = IMG_LoadTexture(window.getRenderer(), "ressources/twoPlayerLocal/orange_crown.png");
}

void TwoPlayerLocalScene::updateScene(GameWindow& window, int deltaTime) {
	Scene::updateScene(window, deltaTime);
	static bool start = false;

	if (time > 2000 && !start) {
		start = true;
		time = 0;
	}
	if (!start) {
		board.turn();
		return;
	}
	while (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		board.turn();
		board.move();
		if (!board.isAlive(0)) {
			std::cout << "Player 1 is dead" << std::endl;
			start = false;
			board.reset();
			board.increaseScore(1);
		} 
		if (!board.isAlive(1)) {
			std::cout << "Player 2 is dead" << std::endl;
			start = false;
			board.reset();
			board.increaseScore(0);
		}
		// if (!snake.isAlive()) {
		// 	game->setScene("gameOver", new int(snake.getScore()));
		// }
	}
}

void TwoPlayerLocalScene::renderObjects(GameWindow& window) {
	board.render(window.getRenderer());
	if (board.getScore(0) > board.getScore(1)) {
		SDL_Rect rect = {97, 326, 327 , 253};
		SDL_RenderCopy(window.getRenderer(), crownP1, NULL, &rect);
	} else if (board.getScore(1) > board.getScore(0)) {
		SDL_Rect rect = {97, 666, 327 , 253};
		SDL_RenderCopy(window.getRenderer(), crownP2, NULL, &rect);
	}
	window.drawNumber(board.getScore(0), 260, 490, 3);
	window.drawNumber(board.getScore(1), 254, 828, 3);
}