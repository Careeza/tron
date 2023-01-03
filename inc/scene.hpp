#ifndef SCENE_HPP

# define SCENE_HPP

# include "render.hpp"
# include "button.hpp"
# include "player.hpp"
# include <vector>
# include <SDL_mixer.h>

class Game;

class Scene {
public:
	Scene();
	~Scene();
	virtual void			handleEvents(Game* game) = 0;
	virtual void			initScene(GameWindow& widnow) = 0;
	virtual void			renderGameObjects(GameWindow& window) {};
	virtual void			updateScene(GameWindow& window, int deltaTime) {};
	std::vector<Button>&	getButtons() { return buttons; };
	void					renderScene(GameWindow& window);
	void					playMusic();
	void					stopMusic();
	virtual void			deleteScene();
protected:
	SDL_Texture					*background;
	std::vector<Button>			buttons;
	Mix_Music 					*music;
	int							time;
};

class MainMenuScene : public Scene {
public:
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
};

class JoinScene : public Scene {
public:
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
	void renderGameObjects(GameWindow& window) override;
private:
	std::vector<int>	roomNumber;
};

//510 18 1392 x 1044
class SinglePlayerScene : public Scene {
public:
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	renderGameObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
	void	deleteScene() override;
private:
	Snake 	snake;
	Map 	map;
};

Button	*handleButtons(Game *game, Scene *scene, SDL_Event& event);
void	exitGame(Game *game);
void	playGame(Game *game);
void	returnToMenu(Game *game);
void	joinGame(Game *game);

#endif