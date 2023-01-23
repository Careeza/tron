#include "player.hpp"
#include "tools.hpp"
#include "game.hpp"
#include <SDL_image.h>
#include <iostream>
#include <sstream>


void	GameBoard::initBoardLocal(SDL_Renderer *renderer) {
	nbPlayers = 2;
	currentPlayer = 0;
	std::vector<std::string>	color = {"Blue", "Orange", "Green", "Purple"};
	std::vector<Position>		playerSpawnPosition({{10, 10}, {164, 120}, {164, 10},  {10, 120}});
	std::vector<DIRECTION>		playerSpawnDirection({DIRECTION::RIGHT, DIRECTION::LEFT, DIRECTION::RIGHT, DIRECTION::LEFT});

	map = std::vector<std::vector<CELL_TYPE>>(MAP_HEIGHT, std::vector<CELL_TYPE>(MAP_WIDTH, CELL_TYPE::EMPTY));
	for (int i = 0; i < 2; i++) {
		players.push_back({playerSpawnPosition[i].first, playerSpawnPosition[i].second, playerSpawnDirection[i], &map});
		players[i].initPlayer(renderer, i);
	}
	if (renderer != NULL) {
		std::string boardTexturePath = "ressources/twoPlayerLocal/background.png";
		boardTexture = IMG_LoadTexture(renderer, boardTexturePath.c_str());
	} 

}

void	GameBoard::initBoard(SDL_Renderer *renderer, int nbPlayers_, int currentPlayer_) {
	std::cout << "[[--HERE--]] : " << currentPlayer_ << std::endl;
	if (currentPlayer_ == -1) {
		initBoardLocal(renderer);
		std::cout << "[[HERE]]" << std::endl;
		return ;
	}
	nbPlayers = nbPlayers_;
	currentPlayer = currentPlayer_;
	std::vector<std::string>	color = {"Blue", "Orange", "Green", "Purple"};
	std::vector<Position>		playerSpawnPosition({{10, 10}, {164, 120}, {164, 10},  {10, 120}});
	std::vector<DIRECTION>		playerSpawnDirection({DIRECTION::RIGHT, DIRECTION::LEFT, DIRECTION::RIGHT, DIRECTION::LEFT});

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

void		GameBoard::reset() {
	map = std::vector<std::vector<CELL_TYPE>>(MAP_HEIGHT, std::vector<CELL_TYPE>(MAP_WIDTH, CELL_TYPE::EMPTY));
	for (int i = 0; i < nbPlayers; i++) {
		players[i].reset();
	}
}

void		GameBoard::increaseScore(int player) {
	players[player].increaseScore(1);
}

int			GameBoard::getScore(int player) {
	return players[player].getScore();
}

Position	GameBoard::getHead(int player) {
	return players[player].getHead();
}

void		GameBoard::updatePlayer(int player, int x, int y, DIRECTION direction_) {
	players[player].updatePlayer(x, y, direction_);
}
