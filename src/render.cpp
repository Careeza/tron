#include "render.hpp"
#include "game.hpp"
#include <iostream>

GameWindow::GameWindow() : window(NULL), renderer(NULL), width(0), height(0), highDPI(1) {}

GameWindow::~GameWindow() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void GameWindow::init() {
	int w, h;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	SDL_GetWindowSize(window, &w, &h);
	SDL_GL_GetDrawableSize(window, &width, &height);
	highDPI = width / w;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
	if (!renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	virtualWindow = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, VIRTUAL_W, VIRTUAL_H);
	if (!virtualWindow) {
		std::cerr << "Virtual window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	// SDL_SetTextureBlendMode(virtualWindow, SDL_BLENDMODE_MUL);
	ratio = static_cast<float>(width) / static_cast<float>(height);
	ratioVirtual = static_cast<float>(VIRTUAL_W) / static_cast<float>(VIRTUAL_H);
	if (ratio < ratioVirtual) {
		virtualWindowRect = {0, static_cast<int>((height - width / ratioVirtual) / 2), width, static_cast<int>(width / ratioVirtual)};
	} else {
		virtualWindowRect = {static_cast<int>((width - height * ratioVirtual) / 2), 0, static_cast<int>(height * ratioVirtual), height};
	}
}

std::tuple<int, int> GameWindow::transformPosition(int x, int y) {
	int xHighDPI = x * highDPI;
	int yHighDPI = y * highDPI;
	int xVirtual = static_cast<int>(static_cast<float>(xHighDPI - virtualWindowRect.x) / static_cast<float>(virtualWindowRect.w) * static_cast<float>(VIRTUAL_W));
	int yVirtual = static_cast<int>(static_cast<float>(yHighDPI - virtualWindowRect.y) / static_cast<float>(virtualWindowRect.h) * static_cast<float>(VIRTUAL_H));
	return (std::make_tuple(xVirtual, yVirtual));
}

void GameWindow::update() {
}

void GameWindow::render() {
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, virtualWindow, NULL, &virtualWindowRect);
	SDL_RenderPresent(renderer);
}

void GameWindow::clean() {

}

SDL_Renderer *GameWindow::getRenderer() {
	return (renderer);
}

int GameWindow::getWidth() {
	return (width);
}

int GameWindow::getHeight() {
	return (height);
}

int GameWindow::getHighDPI() {
	return (highDPI);
}

float GameWindow::getRatio() {
	return (ratio);
}

float GameWindow::getRatioVirtual() {
	return (ratioVirtual);
}

SDL_Texture *GameWindow::getVirtualWindow() {
	return (virtualWindow);
}