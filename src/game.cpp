#include "game.hpp"
#include "timer.hpp"
#include <algorithm>

Game::Game() : quit(false), server(false), gameInfo() {}


void	Game::init() {
	window.init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
	}
	initScenes();
}

void	Game::initScenes() {
	addScene("mainMenu", new MainMenuScene(this));
	addScene("singlePlayer", new SinglePlayerScene(this));
	addScene("joinRoom", new JoinRoomScene(this));
	addScene("joinOrCreateRoom", new JoinOrCreateRoomScene(this));
	addScene("lobby", new LobbyScene(this));
	addScene("gameOver", new GameOverScene(this));
	addScene("onlineGame", new OnlineGameScene(this));
	addScene("twoPlayer", new TwoPlayerLocalScene(this));
}

Scene	*Game::addScene(std::string name, Scene *scene) {
	scenes[name] = scene;
	scene->initScene(window);
	return (scene);
}

void	Game::setScene(std::string name, void *data) {
	// currentScene->stopMusic();
	currentScene = scenes[name];
	currentScene->giveInfo(data);
	// currentScene->playMusic();
}

void	Game::run() {
	Timer		frameRate;
	Timer		gameTimer;

	currentScene = scenes["mainMenu"];
	currentScene->initScene(window);
	// currentScene->playMusic();
	gameTimer.start();
	while (!quit) {
		frameRate.start();
		currentScene->handleEvents(this);
		currentScene->updateScene(window, gameTimer.getTicks());
		gameTimer.start();
		currentScene->renderScene(window);
		window.update();
		window.render();
		if (frameRate.getTicks() < 1000 / 60) {
			SDL_Delay((1000 / 60) - frameRate.getTicks());
		}
	}
}

void	Game::updateRoom() {
}