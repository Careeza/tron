#include "game.hpp"
#include "timer.hpp"
#include <algorithm>

Game::Game() : quit(false), networkLogic(appID, appVersion) {}


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
}

Scene	*Game::addScene(std::string name, Scene *scene) {
	scenes[name] = scene;
	return (scene);
}

void	Game::setScene(std::string name, void *data) {
	currentScene->stopMusic();
	currentScene->deleteScene();
	currentScene = scenes[name];
	currentScene->initScene(window, data);
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

void	Game::connectToNetwork() {
	networkLogic.connect();

	std::cout << "waiting for connection..." << std::endl;
	while (!networkLogic.isConnected()) {
		networkLogic.run();
	}
	std::cout << "connected" << std::endl;
}

void	Game::disconnectFromNetwork() {
	networkLogic.disconnect();
}

void	Game::joinRoom(const std::vector<int>& roomNumber) {
	std::string	roomName = "";
	for (int n : roomNumber) {
		roomName += std::to_string(n);
	}
	// std::cout << "join room " << roomName << std::endl;
	// ExitGames::Common::JString jRoomName = roomName.c_str();
	ExitGames::Common::JString jRoomName = L"test";
	std::cout << "join room " << "[" << jRoomName.UTF8Representation().cstr() << "]" << std::endl;
	networkLogic.joinRoom(jRoomName);
	while (!networkLogic.isRoomJoinedOrCreated()) {
		networkLogic.run();
	}
}

void	Game::createRoom(const std::vector<int>& roomNumber) {
	std::string	roomName = "";
	for (int n : roomNumber) {
		roomName += std::to_string(n);
	}
	// std::cout << "creating room " << roomName << std::endl;
	// ExitGames::Common::JString jRoomName = roomName.c_str();
	ExitGames::Common::JString jRoomName = L"test";
	std::cout << "creating room " << "[" << jRoomName.UTF8Representation().cstr() << "]" << std::endl;
	networkLogic.createRoom(jRoomName);
	while (!networkLogic.isRoomJoinedOrCreated()) {
		networkLogic.run();
	}
}

void	Game::updateRoom() {
	networkLogic.run();
}