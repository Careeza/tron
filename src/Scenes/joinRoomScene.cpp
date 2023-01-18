#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>

void	addNumber(std::vector<int> &roomNumber, int number) {
	if (roomNumber.size() < 6) {
		roomNumber.push_back(number);
	}
}

void JoinRoomScene::handleEvents(Game* game) {
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
				//handle the room number
				case SDLK_0:
					addNumber(roomNumber, 0);
					break;
				case SDLK_1:
					addNumber(roomNumber, 1);
					break;
				case SDLK_2:
					addNumber(roomNumber, 2);
					break;
				case SDLK_3:
					addNumber(roomNumber, 3);
					break;
				case SDLK_4:
					addNumber(roomNumber, 4);
					break;
				case SDLK_5:
					addNumber(roomNumber, 5);
					break;
				case SDLK_6:
					addNumber(roomNumber, 6);
					break;
				case SDLK_7:
					addNumber(roomNumber, 7);
					break;
				case SDLK_8:
					addNumber(roomNumber, 8);
					break;
				case SDLK_9:
					addNumber(roomNumber, 9);
					break;
				case SDLK_BACKSPACE:
					if (roomNumber.size() > 0) {
						roomNumber.pop_back();
					}
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

void JoinRoomScene::initScene(GameWindow& window, void *data) {
	background = IMG_LoadTexture(window.getRenderer(), "ressources/join/join.png");
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	SDL_Texture *joinButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/choose/join_off.png");
	SDL_Texture *joinButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/choose/join_on.png");
	Button joinButton(window.getRenderer(), {751, 815, 418, 211}, joinButtonOff, goToLobby);
	joinButton.addOverTexture(window.getRenderer(), joinButtonOn);

	SDL_DestroyTexture(joinButtonOff);
	SDL_DestroyTexture(joinButtonOn);

	buttons.push_back(joinButton);

	music = NULL;
	roomNumber.clear();

	buttons.push_back(exit);
}

void	JoinRoomScene::renderObjects(GameWindow& window) {
	static Timer	timer;
	static bool		draw = true;
	int 			w = 0;
	int 			h = window.getNumberHeight(2);

	if (!timer.isStarted()) {
		timer.start();
	}
	if (roomNumber.size() > 0) {
		std::string	roomNumberString = "";
		for (int i = 0; i < roomNumber.size(); i++) {
			roomNumberString += std::to_string(roomNumber[i]);
		}
		window.drawNumber(roomNumberString, 960, 540, 2);
		w = window.getNumberWidth(roomNumberString, 2);
		//fill a rect [w + 5, 540 - h / 2, 5, h]
	}
	if (timer.getTicks() > 300) {
		draw = !draw;
		timer.stop();
	}
	if (draw) {
		SDL_Rect rect = {960 + w / 2 + 5, 540 - h / 2, 5, h};
		SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(window.getRenderer(), &rect);
	}
}

void	*JoinRoomScene::getInfo() {
	return (void *)&roomNumber;
}