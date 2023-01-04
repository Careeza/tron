#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>

void	LobbyScene::handleEvents(Game* game) {
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

void	LobbyScene::initScene(GameWindow& window, void *data) {
	background = IMG_LoadTexture(window.getRenderer(), "ressources/joinBackGround.png");
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	music = NULL;
	roomNumber = *(static_cast<std::vector<int> *>(data));

	buttons.push_back(exit);
}

void	LobbyScene::renderGameObjects(GameWindow& window) {
	if (roomNumber.size() > 0) {
		std::string	roomNumberString = "";
		for (int i = 0; i < roomNumber.size(); i++) {
			roomNumberString += std::to_string(roomNumber[i]);
		}
		window.drawNumber(roomNumberString, 960, 540, 2);
	}
}


void	*LobbyScene::getInfo() {
	return (void *)&roomNumber;
}