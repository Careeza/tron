#include "player.hpp"
#include "tools.hpp"
#include "game.hpp"
#include <SDL_image.h>
#include <iostream>

// Player::Player() {
// 	score = 0;
// }

Snake::Snake(int x, int y, int size, DIRECTION direction_, Map *map_) : score(0), direction(direction_), nextDirection(direction_), map(map_), alive(true) {
	for (int i = 0; i < size; i++) {
		body.push_back(std::make_pair(x, y));
		map->at(y)[x] = CELL_TYPE::SNAKE;
	}
}

Snake::~Snake() {
}

void		Snake::initPlayer(SDL_Renderer *renderer) {
	headTextures[DIRECTION::UP] = IMG_LoadTexture(renderer, "ressources/Blue/moto/motoUp.png");
	headTextures[DIRECTION::LEFT] = IMG_LoadTexture(renderer, "ressources/Blue/moto/motoLeft.png");
	headTextures[DIRECTION::RIGHT] = IMG_LoadTexture(renderer, "ressources/Blue/moto/motoRight.png");
	headTextures[DIRECTION::DOWN] = IMG_LoadTexture(renderer, "ressources/Blue/moto/motoDown.png");
	foodTexture.init(renderer, "ressources/Blue/disk/diskAnim.png", 28, 28, 16);
}

void	Snake::move() {
	if (!alive) {
		return;
	}
	map->at(body.back().second)[body.back().first] = CELL_TYPE::EMPTY;
	for (int i = body.size() -1; i > 0; i--) {
		body[i] = body[i - 1];
	}
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
	} else if (map->at(body[0].second)[body[0].first] == CELL_TYPE::SNAKE) {
		die();
		return;
	}
	//check if the head collide with the food
	auto [x, y] = getHead();
	SDL_Rect rect = {x * CELL_SIZE + 510, y * CELL_SIZE + 18, CELL_SIZE, CELL_SIZE};
	auto [fx, fy] = food;
	SDL_Rect rect2 = {fx * CELL_SIZE + 510 - (FOOD_SIZE - CELL_SIZE) / 2, fy * CELL_SIZE + 18 - (FOOD_SIZE - CELL_SIZE) / 2, FOOD_SIZE, FOOD_SIZE};
	if (collide(rect, rect2)) {
		grow();
		increaseScore(10);
		map->at(food.second)[food.first] = CELL_TYPE::EMPTY;
		spawnRandomScene(*map);
	}
	map->at(body[0].second)[body[0].first] = CELL_TYPE::SNAKE;
	foodTexture.update(60);
}

void	Snake::turn() {
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

void	Snake::setDirection(DIRECTION direction) {
	this->direction = direction;
}

void	Snake::setNextDirection(DIRECTION direction) {
	this->nextDirection = direction;
}

DIRECTION	Snake::getDirection() {
	return direction;
}

DIRECTION	Snake::getNextDirection() {
	return nextDirection;
}

void	Snake::increaseScore(int score) {
	this->score += score;
}

int		Snake::getScore() {
	return score;
}

SnakeBody	Snake::getBody() {
	return body;
}

Position	Snake::getHead() {
	return body[0];
}

bool	Snake::isAlive() {
	return alive;
}

void	Snake::die() {
	alive = false;
}

void	Snake::grow() {
	for (int i = 0; i < GROWTH; i++) {
		body.push_back(body.back());
	}
}

void	Snake::spawnRandomScene(Map &map) {
	std::vector<Position>	emptyCells;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == CELL_TYPE::EMPTY) {
				emptyCells.push_back(std::make_pair(j, i));
			}
		}
	}
	if (emptyCells.size() == 0) {
		die();
	}
	int r = getRandomNumber(0, emptyCells.size() - 1);
	food = emptyCells[r];
	map[emptyCells[r].second][emptyCells[r].first] = CELL_TYPE::FOOD;
}

void	Snake::render(SDL_Renderer *renderer) {
	int xStart = 510 - (SNAKE_BODY_SIZE - CELL_SIZE) / 2;
	int yStart = 18 - (SNAKE_BODY_SIZE - CELL_SIZE) / 2;
	for (int i = 1; i < body.size(); i++) {
		auto [x, y] = body[i];
		auto [x2, y2] = body[i - 1];
		SDL_SetRenderDrawColor(renderer, 0x6E, 0xE2, 0xFF, 0xFF - (0xFF - 0x30) * i / body.size());
		SDL_Rect rect = {x * CELL_SIZE + xStart, y * CELL_SIZE + yStart, SNAKE_BODY_SIZE, SNAKE_BODY_SIZE};
		SDL_RenderFillRect(renderer, &rect);
		drawRectBetweenPoints(renderer, x2 * CELL_SIZE + xStart, y2 * CELL_SIZE + yStart, x * CELL_SIZE + SNAKE_BODY_SIZE + xStart, y * CELL_SIZE + SNAKE_BODY_SIZE + yStart);
	}
	auto [x, y] = getHead();
	SDL_Rect rect = {x * CELL_SIZE + 510 - (SNAKE_HEAD_SIZE - CELL_SIZE) / 2, y * CELL_SIZE + 18 - (SNAKE_HEAD_SIZE - CELL_SIZE) / 2, SNAKE_HEAD_SIZE, SNAKE_HEAD_SIZE};
	SDL_RenderCopy(renderer, headTextures[direction], NULL, &rect);
	auto [fx, fy] = food;
	SDL_Rect rect2 = {fx * CELL_SIZE + 510 - (FOOD_SIZE - CELL_SIZE) / 2, fy * CELL_SIZE + 18 - (FOOD_SIZE - CELL_SIZE) / 2, FOOD_SIZE, FOOD_SIZE};
	// SDL_RenderCopy(renderer, foodTexture, NULL, &rect2);
	foodTexture.render(rect2);
}

void	Snake::deletePlayer() {
	SDL_DestroyTexture(headTextures[DIRECTION::UP]);
	SDL_DestroyTexture(headTextures[DIRECTION::RIGHT]);
	SDL_DestroyTexture(headTextures[DIRECTION::DOWN]);
	SDL_DestroyTexture(headTextures[DIRECTION::LEFT]);
}