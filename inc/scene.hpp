#ifndef SCENE_HPP

# define SCENE_HPP

# include "render.hpp"
# include "button.hpp"
# include "player.hpp"
# include <vector>
# include <SDL_mixer.h>
# include "online.hpp"

class Game;

class Scene {
public:
	Scene(Game *game_) : time(0), game(game_) {};
	~Scene();
	virtual void			handleEvents(Game* game) = 0;
	virtual void			initScene(GameWindow& widnow) = 0;
	virtual void			giveInfo(void *data) {};
	virtual void			renderObjects(GameWindow& window) {};
	virtual void			updateScene(GameWindow& window, int deltaTime) {time += deltaTime;};
	std::vector<Button>&	getButtons() { return buttons; };
	virtual void			*getInfo() { return nullptr; };
	void					renderScene(GameWindow& window);
	void					playMusic();
	void					stopMusic();
	virtual void			deleteScene();
protected:
	SDL_Texture					*background;
	std::vector<Button>			buttons;
	Mix_Music 					*music;
	int							time;
	Game						*game;
};

class MainMenuScene : public Scene {
public:
	MainMenuScene(Game *game_) : Scene(game_) {};
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
};


class JoinOrCreateRoomScene : public Scene {
public:
	JoinOrCreateRoomScene(Game *game_) : Scene(game_) {};
	void handleEvents(Game* game) override;
	void initScene(GameWindow& window) override;
private:
};

class JoinRoomScene : public Scene {
public:
	JoinRoomScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	renderObjects(GameWindow& window) override;
	void	*getInfo() override;
private:
	std::vector<int>	roomNumber;
};

class LobbyScene : public Scene {
public:
	LobbyScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	giveInfo(void *data) override;
	void	renderObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
	void	*getInfo() override;
private:
	std::vector<int>			roomNumber;
	int							currentPlayer;
	int							nbPlayers;
	std::vector<SDL_Texture*>	playersNotReady;
	std::vector<SDL_Texture*>	playersReady;
	std::vector<SDL_Texture*>	backgrounds;
	SDL_Texture					*noPlayer;
	gameOnlineInfo				*gameInfo;
};

class OnlineGameScene : public Scene {
public:
	OnlineGameScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	renderObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
	void	giveInfo(void *data) override;
private:
	gameOnlineInfo	*gameInfo;
	GameBoard		board;
};

//510 18 1392 x 1044
class SinglePlayerScene : public Scene {
public:
	SinglePlayerScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	giveInfo(void *data) override;
	void	renderObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
	void	deleteScene() override;
private:
	Snake 	snake;
	Map 	map;
	int		bestScore;
};

class TwoPlayerLocalScene : public Scene {
public:
	TwoPlayerLocalScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	renderObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
private:
	GameBoard	board;
};

class GameOverScene : public Scene {
public:
	GameOverScene(Game *game_) : Scene(game_) {};
	void	handleEvents(Game* game) override;
	void	initScene(GameWindow& window) override;
	void	giveInfo(void *data) override;
	void	renderObjects(GameWindow& window) override;
	void	updateScene(GameWindow& window, int deltaTime) override;
	void	deleteScene() override;
private:
	SDL_Texture			*gameOverTexture;
	AnimatedTexture		skullAnimation;
	AnimatedTexture		bestScoreAnimation;
	int					score;
	bool				bestScoreBeat;
};

Button	*handleButtons(Game *game, Scene *scene, SDL_Event& event);
void	exitGame(Game *game);
void	playGame(Game *game);
void	returnToMenu(Game *game);
void	joinOrCreateRoom(Game *game);
void	createRoom(Game *game);
void	joinRoom(Game *game);
void	goToLobby(Game *game);
void	copyRoomNumber(Game *game);
void	setReady(Game *game);
void	goToTwoPlayers(Game *game);

#endif