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

void JoinOrCreateRoomScene::initScene(GameWindow& window, void *data) {
	background = IMG_LoadTexture(window.getRenderer(), "ressources/choose/chooser_no.png");
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOff.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	music = NULL;

	SDL_Texture *hostButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/choose/host_off.png");
	SDL_Texture *hostButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/choose/host_on.png");
	Button hostButton(window.getRenderer(), {476, 444, 418, 211}, hostButtonOff, createRoom);
	hostButton.addOverTexture(window.getRenderer(), hostButtonOn);

	SDL_DestroyTexture(hostButtonOff);
	SDL_DestroyTexture(hostButtonOn);

	buttons.push_back(hostButton);

	SDL_Texture *joinButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/choose/join_off.png");
	SDL_Texture *joinButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/choose/join_on.png");
	Button joinButton(window.getRenderer(), {1038, 444, 418, 211}, joinButtonOff, joinRoom);
	joinButton.addOverTexture(window.getRenderer(), joinButtonOn);

	SDL_DestroyTexture(joinButtonOff);
	SDL_DestroyTexture(joinButtonOn);

	buttons.push_back(joinButton);


	buttons.push_back(exit);
}