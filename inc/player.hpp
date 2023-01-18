#ifndef PLAYER_HPP

# define PLAYER_HPP

# include <SDL.h>
# include <vector>
# include <map>
# include "render.hpp"

enum struct CELL_TYPE {
	EMPTY,
	FOOD,
	SNAKE,
};

enum struct DIRECTION {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

typedef std::pair<int, int>						Position;
typedef std::vector<Position>		 			SnakeBody;
typedef std::vector<std::vector<CELL_TYPE>>		Map;


class Snake {
public:
	Snake() {};
	Snake(int x, int y, int size, DIRECTION direction_, Map *map_);
	~Snake();
	void		initPlayer(SDL_Renderer *renderer);
	void		move();
	void		turn();
	void		setNextDirection(DIRECTION direction);
	void		setDirection(DIRECTION direction);
	DIRECTION	getDirection();
	DIRECTION	getNextDirection();
	void		increaseScore(int score);
	int			getScore();
	SnakeBody	getBody();
	Position	getHead();
	bool		isAlive();
	void		die();
	void		grow();
	void		spawnRandomScene(Map &map);
	void		render(SDL_Renderer *renderer);
	void		deletePlayer();
private:
	int									score;
	DIRECTION							direction;
	DIRECTION							nextDirection;
	Map									*map;
	bool								alive;
	SnakeBody							body;
	Position							food;
	AnimatedTexture						foodTexture;
	std::map<DIRECTION, SDL_Texture*>	headTextures;
};

#endif