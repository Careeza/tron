#ifndef GAME_HPP

# define GAME_HPP

# include "online.hpp"
# include "render.hpp"
# include "scene.hpp"
# include "player.hpp"
# include "LoadBalancing-cpp/inc/Client.h"
# include "LoadBalancing-cpp/inc/Listener.h"


# include <map>
# include <vector>
# include <string>

# define CELL_SIZE 8
# define FOOD_SIZE 45
# define NB_FRAME_FOOD 18
# define SNAKE_BODY_SIZE 8
# define SNAKE_HEAD_SIZE 72
# define MAP_HEIGHT 1044 / CELL_SIZE
# define MAP_WIDTH 1392 / CELL_SIZE
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
	void	connectToNetwork();
	void	createRoom(const std::vector<int>& roomNumber);
	void	joinRoom(const std::vector<int>& roomNumber);
	void	disconnectFromNetwork();
	void	setScene(std::string name, void *data = nullptr);
	void	quitGame() { quit = true; }
	bool	isQuit() { return (quit); }
	Scene	*getCurrentScene() { return (currentScene); }

	GameWindow& getWindow() { return (window); }
private:
	GameWindow						window;
	std::map<std::string, Scene*>	scenes;
	Scene 							*currentScene;
	bool							quit;

	const ExitGames::Common::JString 	appID = L"0baa921c-75d0-4172-8f0c-1e8ddffeedf8";
	const ExitGames::Common::JString 	appVersion = L"1.0";
	SampleNetworkLogic 					networkLogic;
};

#endif