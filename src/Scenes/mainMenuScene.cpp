#include "game.hpp"
#include "tools.hpp"
#include <iostream>

void MainMenuScene::handleEvents(Game* game) {
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

void MainMenuScene::initScene(GameWindow& window) {
	std::cout << "[[MainMenuScene]]" << std::endl;
	background = IMG_LoadTexture(window.getRenderer(), "ressources/menu/menu.png");
	//make the background an SDL_TEXTUREACCESS_TARGET
	Button play(window.getRenderer(), {105, 370, 701, 111}, NULL, playGame);
	play.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	// Button multiPlayer(window.getRenderer(), {105, 540, 701, 111}, NULL, goToTwoPlayers);
	Button multiPlayer(window.getRenderer(), {105, 540, 701, 111}, NULL, joinOrCreateRoom);
	multiPlayer.addOverTexture(window.getRenderer(), {15, 166, 255, 152});
	SDL_Texture *exitButtonOff = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOff.png");
	SDL_Texture *exitButtonOn = IMG_LoadTexture(window.getRenderer(), "ressources/menu/btn/btnOn.png");
	Button exit(window.getRenderer(), {108, 934, 185, 74}, exitButtonOff, exitGame);
	exit.addOverTexture(window.getRenderer(), exitButtonOn);

	SDL_DestroyTexture(exitButtonOff);
	SDL_DestroyTexture(exitButtonOn);

	buttons.push_back(play);
	buttons.push_back(multiPlayer);
	buttons.push_back(exit);
	// buttons.push_back(settings);
	music = Mix_LoadMUS("ressources/mainMenu.mp3");
	if (!music) {
		fprintf(stderr, "Erreur lors du chargement de la musique [%s]: %s\n", "ressources/mainMenu.mp3", Mix_GetError());
	}
}