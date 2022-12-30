#include "game.hpp"
#include "player.hpp"
#include "tools.hpp"
#include <iostream>

void SinglePlayerScene::handleEvents(Game* game) {
	SDL_Event	event;
	DIRECTION	direction = snake.getNextDirection();

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
	}
	snake.setNextDirection(direction);
}

void SinglePlayerScene::initScene(GameWindow& window) {
	background = copyTexture(window.getRenderer(), IMG_LoadTexture(window.getRenderer(), "ressources/background3.png"));
	SDL_SetRenderTarget(window.getRenderer(), background);
	window.drawNumber(1234567890, 300, 800);
	SDL_SetRenderTarget(window.getRenderer(), NULL);
	map = std::vector<std::vector<CELL_TYPE>>(MAP_HEIGHT, std::vector<CELL_TYPE>(MAP_WIDTH, CELL_TYPE::EMPTY));
	snake = Snake(10, 10, 30, DIRECTION::RIGHT, &map);
	snake.initPlayer(window.getRenderer());
	snake.spawnRandomScene(map);
}

//510 18 1392 x 1044
//256 370
void SinglePlayerScene::renderGameObjects(GameWindow& window) {
	SDL_SetRenderTarget(window.getRenderer(), window.getVirtualWindow());
	SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_NONE);
	snake.render(window.getRenderer());
	window.drawNumber(snake.getScore(), 254, 370);
	SDL_SetRenderTarget(window.getRenderer(), NULL);
}

void SinglePlayerScene::updateScene(GameWindow& window, int deltaTime) {
	time += deltaTime;
	if (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		snake.turn();
		snake.move();
	}
}