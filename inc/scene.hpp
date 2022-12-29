#ifndef SCENE_HPP

# define SCENE_HPP

# include "render.hpp"
# include "button.hpp"
# include "player.hpp"
# include <vector>

class Game;

class Scene {
public:
	Scene();
	~Scene();
	virtual void	handleEvents(Game* game) = 0;
	virtual void	initScene(GameWindow& widnow) = 0;
	virtual void	renderGameObjects(GameWindow& window) {};
	virtual void	updateScene(GameWindow& window, int deltaTime) {};
	void			renderScene(GameWindow& window);
protected:
	SDL_Texture					*background;
	std::vector<Button>			buttons;
	std::vector<SDL_Texture*>	objects;
	int							time;
};

class MainMenuScene : public Scene {
public:
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
};

//510 18 1392 x 1044
class SinglePlayerScene : public Scene {
public:
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
	void renderGameObjects(GameWindow& window) override;
	void updateScene(GameWindow& window, int deltaTime) override;
private:
	Snake 	snake;
	Map 	map;
};

#endif