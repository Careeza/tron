#include "game.hpp"
#include "scene.hpp"
#include "tools.hpp"
#include <iostream>
#include <fstream>
#include "online.hpp"

void	exitGame(Game *game) {
	game->quitGame();
}

void	playGame(Game *game) {
	std::cout << "play game" << std::endl;
	game->setScene("singlePlayer");
}

void	joinOrCreateRoom(Game *game) {
	std::cout << "join or create room" << std::endl;
	game->setScene("joinOrCreateRoom");
}

void	createRoom(Game *game) {
	game->setServer(true);
	goToLobby(game);
	// game->createRoom();
}

void putStringToClipboard(const std::string& str) {
    // Create a temporary file to hold the string
    std::ofstream tempFile("temp.txt");
    tempFile << str;
    tempFile.close();
    
    // Use the system function to execute the pbcopy command
    std::string command = "pbcopy < temp.txt";
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error executing pbcopy command" << std::endl;
    }
    // Delete the temp file
    remove("temp.txt");
}


void	copyRoomNumber(Game *game) {
	std::vector<int> roomNumber = *(std::vector<int> *)(game->getCurrentScene()->getInfo());
	std::string roomNumberString = "";
	for (auto& number : roomNumber) {
		roomNumberString += std::to_string(number);
	}
	putStringToClipboard(roomNumberString);
}

void	setReady(Game *game) {
	std::cout << "set ready" << std::endl;
	gameOnlineInfo *info = &game->getGameInfo();
	info->ready = true;
	std::cout << "READY" << std::endl;
	info->updateClient = true;
	info->updateType = UpdateType::UPDATE_READY;
}

void	goToTwoPlayers(Game *game) {
	std::cout << "HERE" << std::endl;
	game->setScene("twoPlayer");
	std::cout << "HERE" << std::endl;
}

void	goToLobby(Game *game) {
	std::vector<int> 	roomNumber;
	roomInformation		info;

	if (game->isServer()) {
		roomNumber = getRandomNumbers(6);
	} else {
		roomNumber = *static_cast<std::vector<int> *>(game->getCurrentScene()->getInfo());
	}
	info.roomNumber = roomNumber;
	game->setScene("lobby", &info);
}

void	joinRoom(Game *game) {
	std::cout << "join room" << std::endl;
	game->setScene("joinRoom");
}

void	returnToMenu(Game *game) {
	std::cout << "return to menu" << std::endl;
	game->setScene("mainMenu");
}

Button	*handleButtons(Game *game, Scene *scene, SDL_Event& event) {
	std::vector<Button>& buttons = scene->getButtons();
	Button *buttonPressed = nullptr;
	if (event.type == SDL_MOUSEMOTION) {
		for (auto& button : buttons) {
			auto [x, y] = game->getWindow().transformPosition(event.motion.x, event.motion.y);
			if (button.isOver(x, y)) {
				button.setOver(true);
			} else {
				button.setOver(false);
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		for (auto& button : buttons) {
			auto [x, y] = game->getWindow().transformPosition(event.motion.x, event.motion.y);
			if (button.isOver(x, y)) {
				buttonPressed = &button;
			}
		}
	}
	return buttonPressed;
}