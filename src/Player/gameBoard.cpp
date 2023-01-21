#include "player.hpp"
#include "tools.hpp"
#include "game.hpp"
#include <SDL_image.h>
#include <iostream>
#include <sstream>

void	GameBoard::initBoard(SDL_Renderer *renderer, int nbPlayers_, int currentPlayer_) {
	nbPlayers = nbPlayers_;
	currentPlayer = currentPlayer_;
	std::vector<std::string>	color = {"Blue", "Green", "Orange", "Purple"};
	std::vector<Position>		playerSpawnPosition({{10, 10}, {10, 120}, {164, 10}, {164, 120}});
	std::vector<DIRECTION>		playerSpawnDirection({DIRECTION::RIGHT, DIRECTION::RIGHT, DIRECTION::LEFT, DIRECTION::LEFT});

	map = std::vector<std::vector<CELL_TYPE>>(MAP_HEIGHT, std::vector<CELL_TYPE>(MAP_WIDTH, CELL_TYPE::EMPTY));
	for (int i = 0; i < nbPlayers_; i++) {
		players.push_back({playerSpawnPosition[i].first, playerSpawnPosition[i].second, playerSpawnDirection[i], &map});
		players[i].initPlayer(renderer, i);
	}
	if (renderer != NULL) {
		std::string boardTexturePath = "ressources/" + color[currentPlayer] + "/background.png";
		boardTexture = IMG_LoadTexture(renderer, boardTexturePath.c_str());
	} 
}

void	GameBoard::move() {
	for (int i = 0; i < nbPlayers; i++) {
		players[i].move();
	}
}

void	GameBoard::turn() {
	std::cout << "HERE" << std::endl;
	for (int i = 0; i < nbPlayers; i++) {
		players[i].turn();
	}
}

void	GameBoard::setNextDirection(int player, DIRECTION direction) {
	players[player].setNextDirection(direction);
}

DIRECTION	GameBoard::getNextDirection(int player) {
	return players[player].getNextDirection();
}

void		GameBoard::setDirection(int player, DIRECTION direction) {
	players[player].setDirection(direction);
}

DIRECTION	GameBoard::getDirection(int player) {
	return players[player].getDirection();
}

bool		GameBoard::isAlive(int player) {
	return players[player].isAlive();
}

void		GameBoard::die(int player) {
	players[player].die();
}

void		GameBoard::render(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
	for (int i = 0; i < nbPlayers; i++) {
		players[i].render(renderer);
	}
}

std::string		GameBoard::gameBoardToString() {
	std::string str = "";

	str = std::to_string(nbPlayers) + "\n";
	for (int i = 0; i < nbPlayers; i++) {
		str += players[i].playerToString() + "\n";
	}
	return str;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void		GameBoard::stringToGameBoard(std::string str) {
	std::vector<std::string>	strVector = split(str, '\n');
	int							nbPlayers_ = std::stoi(strVector[0]);

	nbPlayers = std::stoi(strVector[0]);
	players.clear();
	for (int i = 0; i < nbPlayers_; i++) {
		players[i].stringToPlayer(strVector[i + 1]);
	}
}