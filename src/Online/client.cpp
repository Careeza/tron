#include "online.hpp"
#include "console.h"
#include "networkLogic.h"
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "tools.hpp"

void	gameStartedClient(NetworkLogic &networkLogic, gameOnlineInfo *gameInfo) {
	while (1) {
		Console::get().update();
		gameInfo->nbPlayers = networkLogic.getNumberOfPlayer();
		if (gameInfo->updateClient) {
			switch (gameInfo->updateType)
			{
			case UpdateType::UPDATE_DIRECTION:
				std::cout << "SEND MESSAGE D" << std::endl;
				networkLogic.sendDirect("D" + std::to_string(gameInfo->currentPlayer) + std::to_string((int)gameInfo->direction));
				break;
			default:
				break;
			}
			gameInfo->updateClient = false;
		}
		if (networkLogic.isUpdate()) {
			std::vector<std::string> updates = networkLogic.getUpdate();
			for (std::string str : updates) {
				std::cout << "RECEIVE MESSAGE : " << str << std::endl;
				if (str[0] == 'D') {
					gameInfo->updateServer = true;
					gameInfo->gameBoardStr = str;
					gameInfo->updateType = UpdateType::UPDATE_GAME;
				}
			}
			// std::string str = networkLogic.getUpdate();
			// gameInfo->gameBoardStr = str;
			// gameInfo->updateServer = true;
			// gameInfo->updateType = UpdateType::UPDATE_GAME;
			networkLogic.setUpdate(false);
		}
		networkLogic.run();
		SLEEP(10);
	}
}

void	lobbyClient(NetworkLogic &networkLogic, gameOnlineInfo *gameInfo) {
	while (1) {
		Console::get().update();
		gameInfo->nbPlayers = networkLogic.getNumberOfPlayer();
		if (gameInfo->updateClient) {
			switch (gameInfo->updateType) {
			case UpdateType::UPDATE_READY:
				std::cout << "SEND MESSAGE R" << std::endl;
				networkLogic.sendDirect("R" + std::to_string(gameInfo->currentPlayer));
				break;
			default:
				break;
			}
			gameInfo->updateClient = false;
		}
		if (networkLogic.isUpdate()) {
			std::vector<std::string> updates = networkLogic.getUpdate();
				for (std::string str : updates) {
					if (str[0] == 'R') {
					int n = std::stoi(str.substr(1)) - 1;
					gameInfo->playerReady[n] = !gameInfo->playerReady[n];
					gameInfo->updateType = UpdateType::UPDATE_READY;
				} else if (str[0] == 'S') {
					gameInfo->updateType = UpdateType::UPDATE_START;
					gameInfo->updateServer = true;
					gameStartedClient(networkLogic, gameInfo);
				}
			}
			gameInfo->updateServer = true;
		}
		networkLogic.run();
		SLEEP(10);
	}
}

void	client(bool *created, std::string roomName, gameOnlineInfo *gameInfo) {
	std::cout << "Client" << std::endl;
	NetworkLogic networkLogic(&Console::get());

	ExitGames::Common::JString jRoomName = roomName.c_str();
	networkLogic.setRoomName(jRoomName);
	networkLogic.connect();
	while(networkLogic.getLastInput() != INPUT_EXIT && networkLogic.getState() != STATE_DISCONNECTED) {
		if (networkLogic.getState() == STATE_CONNECTED && networkLogic.getState() != STATE_JOINED) {
			std::cout << "Join room" << std::endl;
			networkLogic.setLastInput(INPUT_JOIN_ROOM);
		}
		if (networkLogic.getState() == STATE_JOINED) {
			std::cout << "Room Joined" << std::endl;
			break;
		}
		networkLogic.run();
		Console::get().update();
		SLEEP(100);
	}
	gameInfo->currentPlayer = networkLogic.getCurrentNumber();
	*created = true;
	lobbyClient(networkLogic, gameInfo);
}

void	createClient(std::vector<int> roomNumber, gameOnlineInfo *gameInfo) {
	std::string	roomName = "";
	for (int i = 0; i < roomNumber.size(); i++) {
		roomName += std::to_string(roomNumber[i]);
	}
	bool	created = false;
	std::thread	listenerThread(client, &created, roomName, gameInfo);
	listenerThread.detach();
	while (!created) {
		SLEEP(100);
	}
	std::cout << "Server join" << std::endl;
}
