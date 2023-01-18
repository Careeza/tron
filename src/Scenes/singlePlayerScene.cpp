#include "game.hpp"
#include "player.hpp"
#include "tools.hpp"
#include <iostream>

void SinglePlayerScene::handleEvents(Game* game) {
	static SDL_Event	event;
	DIRECTION			direction = snake.getNextDirection();
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
	} else {
		snake.setNextDirection(direction);
	}
}

void SinglePlayerScene::initScene(GameWindow& window, void *data) {
	std::cout << "[[SinglePlayerScene]]" << std::endl;
	background = IMG_LoadTexture(window.getRenderer(), "ressources/game/background.png");
	SDL_SetRenderTarget(window.getRenderer(), NULL);
	map = std::vector<std::vector<CELL_TYPE>>(MAP_HEIGHT, std::vector<CELL_TYPE>(MAP_WIDTH, CELL_TYPE::EMPTY));
	snake = Snake(10, 10, 30, DIRECTION::RIGHT, &map);
	snake.initPlayer(window.getRenderer());
	snake.spawnRandomScene(map);

	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, returnToMenu);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	buttons.push_back(exit);

	music = Mix_LoadMUS("ressources/gamePlay.mp3");
	if (!music) {
		std::cout << "Error loading music: " << Mix_GetError() << std::endl;
	}
}

//510 18 1392 x 1044
//256 370
void SinglePlayerScene::renderObjects(GameWindow& window) {
	SDL_SetRenderTarget(window.getRenderer(), window.getVirtualWindow());
	SDL_SetRenderDrawBlendMode(window.getRenderer(), SDL_BLENDMODE_NONE);
	snake.render(window.getRenderer());
	window.drawNumber(snake.getScore(), 254, 370);
	SDL_SetRenderTarget(window.getRenderer(), NULL);
}

void SinglePlayerScene::updateScene(GameWindow& window, int deltaTime) {
	Scene::updateScene(window, deltaTime);
	if (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		snake.turn();
		snake.move();
		if (!snake.isAlive()) {
			game->setScene("gameOver", new int(snake.getScore()));
		}
	}
}

void SinglePlayerScene::deleteScene() {
	SDL_DestroyTexture(background);
	for (auto button : buttons) {
		if (button.getTexture()) {
			SDL_DestroyTexture(button.getTexture());
		}
		if (button.getOverTexture()) {
			SDL_DestroyTexture(button.getOverTexture());
		}
	}
	Mix_FreeMusic(music);
	snake.deletePlayer();
}