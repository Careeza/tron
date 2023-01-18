#ifndef GAME_HPP

# define GAME_HPP

# include "render.hpp"
# include "scene.hpp"
# include "player.hpp"
# include "online.hpp"


# include <map>
# include <vector>
# include <string>
#include <thread>
#include <iostream>
#include <atomic>

# define CELL_SIZE 8
# define FOOD_SIZE 45
# define NB_FRAME_FOOD 18
# define SNAKE_BODY_SIZE 8
# define SNAKE_HEAD_SIZE 72
# define MAP_HEIGHT 1044 / CELL_SIZE //130
# define MAP_WIDTH 1392 / CELL_SIZE //174
# define SNAKE_SPEED 15
# define GROWTH 10

class Game
{
public:
	Game();
	~Game() {};
	void	init();
	void	initScenes();
	void	run();
	Scene	*addScene(std::string name, Scene *scene);
	void	createRoom(const std::vector<int>& roomNumber);
	void	joinRoom(const std::vector<int>& roomNumber);
	void	updateRoom();
	void	setScene(std::string name, void *data = nullptr);
	void	quitGame() { quit = true; }
	bool	isQuit() { return (quit); }
	Scene	*getCurrentScene() { return (currentScene); }
	void	setServer(bool server) { this->server = server; }
	bool	isServer() { return (server); }
	gameOnlineInfo	&getGameInfo() { return (gameInfo); }
	GameWindow& getWindow() { return (window); }

private:
	GameWindow						window;
	std::map<std::string, Scene*>	scenes;
	Scene 							*currentScene;
	bool							quit;
	bool							server;
	gameOnlineInfo					gameInfo;
};

struct roomInformation {
	std::vector<int>	roomNumber;
	int					nbPlayer;
	int					currentPlayer;
};

#endif