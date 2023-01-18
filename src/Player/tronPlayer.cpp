#include "player.hpp"
#include "tools.hpp"
#include "game.hpp"
#include <SDL_image.h>
#include <iostream>
#include <sstream>

TronPlayer::TronPlayer(int x, int y, DIRECTION direction_, Map *map_) : score(0), direction(direction_), nextDirection(direction_), map(map_), alive(true) {
	body.push_back(std::make_pair(x, y));
	map->at(y)[x] = CELL_TYPE::SNAKE;
}

void	TronPlayer::initPlayer(SDL_Renderer *renderer, int currentPlayer_) {
	std::vector<std::string>	color = {"Blue", "Green", "Orange", "Purple"};
	std::string	path = "ressources/" + color[currentPlayer_] + "/moto";
	headTextures[DIRECTION::UP] = IMG_LoadTexture(renderer, (path + "motoUp.png").c_str());
	headTextures[DIRECTION::LEFT] = IMG_LoadTexture(renderer, (path + "motoLeft.png").c_str());
	headTextures[DIRECTION::RIGHT] = IMG_LoadTexture(renderer, (path + "motoRight.png").c_str());
	headTextures[DIRECTION::DOWN] = IMG_LoadTexture(renderer, (path + "motoDown.png").c_str());
	if (currentPlayer_ == 1) {
		bodyColor = {0x6E, 0xE2, 0xFF, 0xFF};
	} else if (currentPlayer_ == 2) {
		bodyColor = {0x00, 0xFF, 0x00, 0xFF};
	} else if (currentPlayer_ == 3) {
		bodyColor = {0xFF, 0x7F, 0x00, 0xFF};
	} else {
		bodyColor = {0x7F, 0x00, 0xFF, 0xFF};
	}
}

void	TronPlayer::move() {
	if (!alive) {
		return;
	}
	body.insert(body.begin(), std::make_pair(body[0].first, body[0].second));
	if (direction == DIRECTION::UP) {
		body[0].second--;
	} else if (direction == DIRECTION::RIGHT) {
		body[0].first++;
	} else if (direction == DIRECTION::DOWN) {
		body[0].second++;
	} else if (direction == DIRECTION::LEFT) {
		body[0].first--;
	}
	if (body[0].first < 0 || body[0].first >= map->at(0).size() || body[0].second < 0 || body[0].second >= map->size()) {
		die();
		return;
	}
	if (map->at(body[0].second)[body[0].first] == CELL_TYPE::SNAKE) {
		die();
		return;
	}
	map->at(body[0].second)[body[0].first] = CELL_TYPE::SNAKE;
}

void	TronPlayer::turn() {
	if (nextDirection == DIRECTION::UP && this->direction != DIRECTION::DOWN) {
		setDirection(DIRECTION::UP);
	} else if (nextDirection == DIRECTION::RIGHT && this->direction != DIRECTION::LEFT) {
		setDirection(DIRECTION::RIGHT);
	} else if (nextDirection == DIRECTION::DOWN && this->direction != DIRECTION::UP) {
		setDirection(DIRECTION::DOWN);
	} else if (nextDirection == DIRECTION::LEFT && this->direction != DIRECTION::RIGHT) {
		setDirection(DIRECTION::LEFT);
	}
}

void	TronPlayer::setDirection(DIRECTION direction) {
	this->direction = direction;
}

void	TronPlayer::setNextDirection(DIRECTION direction) {
	this->nextDirection = direction;
}

DIRECTION	TronPlayer::getDirection() {
	return direction;
}

DIRECTION	TronPlayer::getNextDirection() {
	return nextDirection;
}

void	TronPlayer::increaseScore(int score) {
	this->score += score;
}

int		TronPlayer::getScore() {
	return score;
}

SnakeBody	TronPlayer::getBody() {
	return body;
}

std::pair<int, int>	TronPlayer::getHead() {
	return body[0];
}

void		TronPlayer::setBody(SnakeBody body_) {
	body = body_;
}

bool	TronPlayer::isAlive() {
	return alive;
}

void	TronPlayer::die() {
	alive = false;
}

void	TronPlayer::render(SDL_Renderer *renderer) {
	int xStart = 510 - (SNAKE_BODY_SIZE - CELL_SIZE) / 2;
	int yStart = 18 - (SNAKE_BODY_SIZE - CELL_SIZE) / 2;
	for (int i = 1; i < body.size(); i++) {
		auto [x, y] = body[i];
		auto [x2, y2] = body[i - 1];
		SDL_SetRenderDrawColor(renderer, bodyColor[0], bodyColor[1], bodyColor[2], bodyColor[3]);
		SDL_Rect rect = {x * CELL_SIZE + xStart, y * CELL_SIZE + yStart, SNAKE_BODY_SIZE, SNAKE_BODY_SIZE};
		SDL_RenderFillRect(renderer, &rect);
		drawRectBetweenPoints(renderer, x2 * CELL_SIZE + xStart, y2 * CELL_SIZE + yStart, x * CELL_SIZE + SNAKE_BODY_SIZE + xStart, y * CELL_SIZE + SNAKE_BODY_SIZE + yStart);
	}
	if (isAlive()) {
		auto [x, y] = getHead();
		SDL_Rect rect = {x * CELL_SIZE + 510 - (SNAKE_HEAD_SIZE - CELL_SIZE) / 2, y * CELL_SIZE + 18 - (SNAKE_HEAD_SIZE - CELL_SIZE) / 2, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE};
		SDL_RenderCopy(renderer, headTextures[direction], NULL, &rect);
	}
}

std::string	TronPlayer::playerToString() {
	std::string str = std::to_string(body.size()) + " ";
	for (auto [x, y] : body) {
		str += std::to_string(x) + " " + std::to_string(y) + " ";
	}
	return str;
}

void		TronPlayer::stringToPlayer(std::string str) {
	std::stringstream ss(str);
	int size;
	ss >> size;
	body.clear();
	for (int i = 0; i < size; i++) {
		int x, y;
		ss >> x >> y;
		body.push_back(std::make_pair(x, y));
	}
}