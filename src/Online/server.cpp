#include "console.h"
#include "networkLogic.h"
#include "online.hpp"
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "tools.hpp"
#include "player.hpp"

void	gameStarted(NetworkLogic *networkLogic) {
	std::cout << "SEGAFAULT 1" << std::endl;
	GameBoard	gameBoard;
	int			nbPlayer = networkLogic->getNumberOfPlayer();
	std::vector<DIRECTION>	direction;

	gameBoard.initBoard(NULL, nbPlayer, 0);
	for (int i = 0; i < nbPlayer; i++) {
		direction.push_back(gameBoard.getDirection(i));
	}
	while (1) {
		for (int i = 0; i < nbPlayer; i++) {
			gameBoard.setNextDirection(i, DIRECTION::RIGHT);
		}
		if (networkLogic->isUpdate()) {
			std::string str = networkLogic->getUpdate();
			if (str[0] == 'D') {
				int n = str[1] - '0';
				int d = str[2] - '0';
				gameBoard.setNextDirection(n, (DIRECTION)d);
			}
			networkLogic->setUpdate(false);
		}
		gameBoard.turn();
		gameBoard.move();
		networkLogic->sendDirect(gameBoard.gameBoardToString());
		networkLogic->run();
		Console::get().update();
		SLEEP(10);
	}

}

void	server(bool *created, std::string roomName) {
	gameOnlineInfo gameInfo;

	std::cout << "Server" << std::endl;
	NetworkLogic networkLogic(&Console::get());
	std::cout << "creating room " << roomName << std::endl;
	ExitGames::Common::JString jRoomName = roomName.c_str();
	networkLogic.setRoomName(jRoomName);
	networkLogic.connect();
	while(networkLogic.getLastInput() != INPUT_EXIT && networkLogic.getState() != STATE_DISCONNECTED) {
		if (networkLogic.getState() == STATE_CONNECTED && networkLogic.getState() != STATE_JOINED) {
			std::cout << "Create room" << std::endl;
			networkLogic.setLastInput(INPUT_CREATE_ROOM);
		}
		if (networkLogic.getState() == STATE_JOINED) {
			std::cout << "Room created" << std::endl;
			break;
		}
		networkLogic.run();
		Console::get().update();
		SLEEP(100);
	}
	*created = true;
	while (1) {
		if (networkLogic.isUpdate()) {
			std::string str = networkLogic.getUpdate();
			if (str[0] == 'R') {
				int n = std::stoi(str.substr(1)) - 1;
				std::cout << "Player " << n + 1 << " ready" << std::endl;
				gameInfo.playerReady[n] = true;
			}
			networkLogic.setUpdate(false);
		}
		bool	shouldStart = false;
		if (networkLogic.getNumberOfPlayer() >= 2) {
			shouldStart = true;
			int nb = networkLogic.getNumberOfPlayer();
			// std::cout << "nb player " << nb << std::endl;
			for (int i = 0; i < nb; i++) {
				if (!gameInfo.playerReady[i]) {
					// std::cout << "player " << i + 1 << " not ready" << std::endl;
					shouldStart = false;
					break;
				}
			}
		}
		if (shouldStart) {
			std::cout << "Start game" << std::endl;
			networkLogic.sendDirect("Start");
			gameStarted(&networkLogic);
			break;
		}
		networkLogic.run();
		Console::get().update();
		SLEEP(10);
	}
}

void	createServer(std::vector<int> roomNumber) {
	std::string	roomName = "";
	for (int i = 0; i < roomNumber.size(); i++) {
		roomName += std::to_string(roomNumber[i]);
	}
	bool	created = false;
	std::cout << "Create server" << std::endl;
	std::thread	listenerThread(server, &created, roomName);
	listenerThread.detach();
	while (!created) {
		SLEEP(100);
	}
	std::cout << "Server created" << std::endl;
}