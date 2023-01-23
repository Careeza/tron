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

void	gameStartedServer(NetworkLogic& networkLogic) {
	// GameBoard	gameBoard;
	// int			nbPlayer = networkLogic.getNumberOfPlayer();
	// std::vector<DIRECTION>	direction;

	// gameBoard.initBoard(NULL, nbPlayer, 0);
	// for (int i = 0; i < nbPlayer; i++) {
	// 	direction.push_back(gameBoard.getDirection(i));
	// }
	while (1) {
		if (networkLogic.isUpdate()) {
			std::vector<std::string> updates = networkLogic.getUpdate();
			for (std::string str : updates) {
				if (str[0] == 'D') {
					// int n = str[1] - '0';
					// int d = str[2] - '0';
					// gameBoard.setNextDirection(n, (DIRECTION)d);
					std::cout << "SERVER SEND MESSAGE" << std::endl;
					networkLogic.sendDirect(str);
				}
				networkLogic.setUpdate(false);
			}
		}
		networkLogic.run();
		Console::get().update();
		SLEEP(10);

	}
	// 	gameBoard.turn();
	// 	gameBoard.move();
	// 	networkLogic.sendDirect(gameBoard.gameBoardToString());
	// 	networkLogic.run();
	// 	Console::get().update();
	// 	SLEEP(10);
	// }
}

void	lobbyServer(NetworkLogic& networkLogic) {
	std::cout << "Lobby" << std::endl;
	std::vector<bool> playerReady = {false, false, false, false};

	while (1) {
		if (networkLogic.isUpdate()) {
			std::vector<std::string> updates = networkLogic.getUpdate();
			for (std::string str : updates) {
				if (str[0] == 'R') {
					int n = std::stoi(str.substr(1)) - 1;
					std::cout << "Player " << n + 1 << " ready" << std::endl;
					playerReady[n] = !playerReady[n];
					networkLogic.sendDirect(str);
				} else if (str[0] == 'U') {
					int n = std::stoi(str.substr(1)) - 1;
					std::cout << "Player " << n + 1 << " unready" << std::endl;
					playerReady[n] = false;
					networkLogic.sendDirect(str);
				} else if (str[0] == 'J') {
					int n = std::stoi(str.substr(1)) - 1;
					for (int i = 0; i < 4; i++) {
						if (playerReady[i]) {
							networkLogic.sendDirect("R" + std::to_string(i + 1), n);
						}
					}
				} else if (str[0] == 'L') {
					int n = std::stoi(str.substr(1)) - 1;
					std::cout << "Player " << n + 1 << " left" << std::endl;
				}
			}
		}
		bool	shouldStart = false;
		int nb = networkLogic.getNumberOfPlayer();
		if (nb >= 2) {
			shouldStart = true;
			for (int i = 0; i < nb; i++) {
				if (!playerReady[i]) {
					// std::cout << "player " << i + 1 << " not ready" << std::endl;
					shouldStart = false;
					break;
				}
			}
		}
		if (shouldStart) {
			std::cout << "Start game" << std::endl;
			networkLogic.sendDirect("S");
			gameStartedServer(networkLogic);
			break;
		}
		networkLogic.run();
		Console::get().update();
		SLEEP(10);
	}
}

void	server(bool *created, std::string roomName) {

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
	lobbyServer(networkLogic);
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