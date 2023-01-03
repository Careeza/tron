#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>

void JoinOrCreateRoomScene::handleEvents(Game* game) {
	static SDL_Event	event;
	Button				*buttonPressed = nullptr;

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
		buttonPressed = handleButtons(game, this, event);
	}
	if (buttonPressed) {
		buttonPressed->onClickEvent(game);
	}
}

void JoinOrCreateRoomScene::initScene(GameWindow& window) {
	background = IMG_LoadTexture(window.getRenderer(), "ressources/joinBackGround.png");
	Button join(window.getRenderer(), {480, 500, 320, 80}, NULL, joinRoom);
	join.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	Button create(window.getRenderer(), {1120, 500, 320, 80}, NULL, createRoom);
	create.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	music = NULL;

	buttons.push_back(exit);
	buttons.push_back(join);
	buttons.push_back(create);
}