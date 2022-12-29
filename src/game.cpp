#include "game.hpp"
#include "timer.hpp"
#include <algorithm>

void	Game::init() {
	window.init();

	Scene *menu = addScene("mainMenu", new MainMenuScene());
	menu->initScene(getWindow());

	Scene *singlePlayer = addScene("singlePlayer", new SinglePlayerScene());
	singlePlayer->initScene(getWindow());
}

void	Game::run() {
	Timer		frameRate;
	Timer		gameTimer;
	
	currentScene = scenes["mainMenu"];
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

Scene	*Game::addScene(std::string name, Scene *scene) {
	scenes[name] = scene;
	return (scene);
}

void	Game::setScene(std::string name) {
	currentScene = scenes[name];
}