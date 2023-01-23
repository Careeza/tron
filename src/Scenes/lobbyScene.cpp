#include "game.hpp"
#include "tools.hpp"
#include <iostream>
#include "timer.hpp"
#include <string>
#include "online.hpp"

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

void	LobbyScene::initScene(GameWindow& window) {
	gameInfo = &game->getGameInfo();
	music = NULL;
	nbPlayers = gameInfo->nbPlayers;
	currentPlayer = gameInfo->currentPlayer;
	std::string path = "ressources/party/p" + std::to_string(currentPlayer) + "_party.png";
	background = IMG_LoadTexture(window.getRenderer(), path.c_str());
	for (int i = 0; i < 4; i++) {
		std::string pathNR = "ressources/party/p" + std::to_string(i + 1) + ".png";
		std::string pathR = "ressources/party/p" + std::to_string(i + 1) + "_ready.png";
		playersNotReady.push_back(IMG_LoadTexture(window.getRenderer(), pathNR.c_str()));
		playersReady.push_back(IMG_LoadTexture(window.getRenderer(), pathR.c_str()));
	}
	noPlayer = IMG_LoadTexture(window.getRenderer(), "ressources/party/empty_party.png");
	//1146 392
	Button copy(window.getRenderer(), {1146, 392, 114, 124}, NULL, copyRoomNumber);
	buttons.push_back(copy);
	Button ready(window.getRenderer(), {748, 565, 418, 124}, NULL, setReady);
	buttons.push_back(ready);
}

void	LobbyScene::giveInfo(void *data) {
	roomInformation *info = (roomInformation*)data;
	roomNumber = info->roomNumber;
	if (game->isServer()) {
		createServer(roomNumber);
		createClient(roomNumber, gameInfo);
	} else {
		createClient(roomNumber, gameInfo);
	}
}

void	LobbyScene::renderObjects(GameWindow& window) {
	if (roomNumber.size() > 0) {
		window.setColor(currentPlayer - 1);
		std::string	roomNumberString = "";
		for (int i = 0; i < roomNumber.size(); i++) {
			roomNumberString += std::to_string(roomNumber[i]);
		}
		window.drawNumber(roomNumberString, 910, 452, 2.2);
	}
	std::vector<Position>	positions({{50, 50}, {1310, 50}, {50, 824}, {1310, 824}});
	for (int i = 0; i < 4; i++) {
		SDL_Texture	*texture;
		if (i < gameInfo->nbPlayers) {
			if (gameInfo->playerReady[i]) {
				texture = playersReady[i];
			} else {
				texture = playersNotReady[i];

			}
		} else {
			texture = noPlayer;
		}
		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		SDL_Rect rect = {positions[i].first, positions[i].second, w, h};
		SDL_RenderCopy(window.getRenderer(), texture, NULL, &rect);
	}
}


void	*LobbyScene::getInfo() {
	return (void *)&roomNumber;
}

void	LobbyScene::updateScene(GameWindow& window, int deltaTime) {
	Scene::updateScene(window, deltaTime);
	if (gameInfo->updateServer) {
		gameInfo->updateServer = false;
		if (gameInfo->updateType == UpdateType::UPDATE_START) {
			std::cout << "START" << std::endl;
			game->setScene("onlineGame", NULL);
		}
	}
	(void)window;
}