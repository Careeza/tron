#include "game.hpp"
#include "timer.hpp"
#include <algorithm>

void	Game::init() {
	window.init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
	}
	initScenes();
}

void	Game::initScenes() {
	addScene("mainMenu", new MainMenuScene());
	addScene("singlePlayer", new SinglePlayerScene());
	addScene("joinGame", new JoinScene());
}

Scene	*Game::addScene(std::string name, Scene *scene) {
	scenes[name] = scene;
	return (scene);
}

void	Game::setScene(std::string name) {
	currentScene->stopMusic();
	currentScene->deleteScene();
	currentScene = scenes[name];
	currentScene->initScene(window);
	currentScene->playMusic();
}

void	Game::run() {
	Timer		frameRate;
	Timer		gameTimer;

	currentScene = scenes["mainMenu"];
	currentScene->initScene(window);
	currentScene->playMusic();
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