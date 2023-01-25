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
	void		spawnPlayer(int x, int y, int size, DIRECTION direction_, Map *map_);
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

class TronPlayer {
	public:
		TronPlayer() {};
		TronPlayer(int x, int y, DIRECTION direction_, Map *map_);
		void		initPlayer(SDL_Renderer *renderer, int currentPlayer_);
		void		move(bool checkCollision = true);
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
		void		render(SDL_Renderer *renderer);
		void		setBody(SnakeBody body_);
		void		reset();
		void		updatePlayer(std::vector<std::string>& updates, int start, int n);
		void		fillPlayer(int x1, int y1, int x2, int y2);
		void		printPlayer();
	private:
		int									score;
		DIRECTION							direction;
		DIRECTION							nextDirection;
		std::map<DIRECTION, SDL_Texture*>	headTextures;
		Map									*map;
		bool								alive;
		SnakeBody							body;
		std::vector<int>					bodyColor;
		int									initialX;
		int									initialY;
		DIRECTION							initialDirection;
};

class GameBoard {
	public:
		GameBoard() {};
		~GameBoard() {};
		void		initBoard(SDL_Renderer *renderer, int nbPlayers_, int currentPlayer_);
		void		initBoardLocal(SDL_Renderer *renderer);
		void		move(bool checkCollision = true);
		bool		turn();
		void		setNextDirection(int player, DIRECTION direction);
		DIRECTION	getNextDirection(int player);
		void		setDirection(int player, DIRECTION direction);
		DIRECTION	getDirection(int player);
		Position	getHead(int player);
		bool		isAlive(int player);
		void		die(int player);
		void		render(SDL_Renderer *renderer);
		void		reset();
		void		increaseScore(int player);
		int			getScore(int player);
		void		updateGameBoard(std::vector<std::string>& updates, int n);
		void		printGameBoard();
	private:
		std::vector<TronPlayer>							players;
		Map												map;
		std::vector<std::map<DIRECTION, SDL_Texture*>>	headTextures;
		SDL_Texture										*boardTexture;
		int												nbPlayers;
		int												currentPlayer;
};

#endif