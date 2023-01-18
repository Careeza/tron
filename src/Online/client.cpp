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
				networkLogic.sendDirect("D" + std::to_string((int)gameInfo->direction));
				gameInfo->updateClient = false;
				break;
			default:
				break;
			}
		}
		if (networkLogic.isUpdate()) {
			std::string str = networkLogic.getUpdate();
			if (str[0] == 'R') {
				int n = std::stoi(str.substr(1)) - 1;
				gameInfo->playerReady[n] = true;
				gameInfo->updateType = UpdateType::UPDATE_READY;
				gameInfo->updateServer = true;
			} else if (str[0] == 'S') {
				gameInfo->updateType = UpdateType::UPDATE_START;
				gameInfo->updateServer = true;
				gameStartedClient(networkLogic, gameInfo);
			}
			networkLogic.setUpdate(false);
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
	while (1) {
		Console::get().update();
		gameInfo->nbPlayers = networkLogic.getNumberOfPlayer();
		if (gameInfo->updateClient) {
			switch (gameInfo->updateType)
			{
			case UpdateType::UPDATE_READY:
				networkLogic.sendDirect("R" + std::to_string(gameInfo->currentPlayer));
				gameInfo->updateClient = false;
				break;
			
			default:
				break;
			}
		}
		if (networkLogic.isUpdate()) {
			std::string str = networkLogic.getUpdate();
			if (str[0] == 'R') {
				int n = std::stoi(str.substr(1)) - 1;
				gameInfo->playerReady[n] = true;
				gameInfo->updateType = UpdateType::UPDATE_READY;
				gameInfo->updateServer = true;
			} else if (str[0] == 'S') {
				gameInfo->updateType = UpdateType::UPDATE_START;
				gameInfo->updateServer = true;
				gameStartedClient(networkLogic, gameInfo);
			}
			networkLogic.setUpdate(false);
		}
		networkLogic.run();
		SLEEP(10);
	}
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
	std::cout << "Server created" << std::endl;
}
