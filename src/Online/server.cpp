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
#include "timer.hpp"
#include "game.hpp"

void	updatePositions(std::vector<std::vector<Position>>& positions, GameBoard& board, int nbPlayer) {
	for (int i = 0; i < nbPlayer; i++) {
		positions[i].push_back(board.getHead(i));
	}
}

void	sendPositions(NetworkLogic& networkLogic, std::vector<std::vector<Position>>& positions, GameBoard& board) {
	std::string	message = "P\n" + std::to_string(positions[0].size()) + "\n";
	message += std::to_string(GETTIMEMS()) + "\n";
	int			i = 0;
	for (auto &pos : positions) {
		for (auto &p : pos) {
			message += std::to_string(p.first) + " " + std::to_string(p.second) + "\n";
		}
		message += std::to_string((int)board.getDirection(i)) + "\n";
		i++;
	}
	networkLogic.sendDirect(message);
}

void	simulateGame(NetworkLogic& networkLogic, GameBoard& board, int& time, std::vector<std::vector<Position>>& positions, int nbPlayer) {
	static bool start = false;

	if (time > 2000 && !start) {
		start = true;
		time = 0;
		unsigned long sendAt = GETTIMEMS();
		std::string message = "S " + std::to_string(sendAt);
		std::cout << "SENDING : " << message << std::endl;
		networkLogic.sendDirect(message);
	}
	if (!start) {
		// board.turn();
		return;
	}
	while (time > SNAKE_SPEED) {
		time -= SNAKE_SPEED;
		if (board.turn()) {
			std::cout << "UPDATE" << std::endl;
			updatePositions(positions, board, nbPlayer);
			sendPositions(networkLogic, positions, board);
		}
		board.move();
		for (int i = 0; i < nbPlayer; i++) {
			if (board.isAlive(i) == false) {
				networkLogic.sendDirect("D" + std::to_string(i + 1));
			}
		}
	}
}

void	gameStartedServer(NetworkLogic& networkLogic) {
	GameBoard	gameBoard;
	int			nbPlayer = networkLogic.getNumberOfPlayer();
	Timer		gameTimer;
	int			time = 0;

	std::vector<std::vector<Position>>	positions(nbPlayer);
	gameBoard.initBoard(NULL, nbPlayer, 0);
	updatePositions(positions, gameBoard, nbPlayer);
	// for (int i = 0; i < nbPlayer; i++) {
	// 	direction.push_back(gameBoard.getDirection(i));
	// }
	gameTimer.start();
	while (1) {
		if (networkLogic.isUpdate()) {
			std::vector<std::string> updates = networkLogic.getUpdate();
			for (std::string str : updates) {
				if (str[0] == 'D') {
					int n = str[1] - '0' - 1;
					int d = str[2] - '0';
					gameBoard.setNextDirection(n, (DIRECTION)d);
				}
				networkLogic.setUpdate(false);
			}
		}
		time += gameTimer.getTicks();
		simulateGame(networkLogic, gameBoard, time, positions, nbPlayer);
		gameTimer.start();
		networkLogic.run();
		Console::get().update();
		SLEEP(10);
	}
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