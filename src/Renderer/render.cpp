#include "render.hpp"
#include "game.hpp"
#include <cmath>
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
	window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	SDL_GetWindowSize(window, &w, &h);
	SDL_GL_GetDrawableSize(window, &width, &height);
	highDPI = width / w;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
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
	neoNumberRenderer.init(renderer);
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

void GameWindow::drawNumber(int number, int x, int y, float ratio, DRAW_MODE mode) {
	switch (mode) {
		case DRAW_MODE::LEFT:
			neoNumberRenderer.drawLeft(getRenderer(), number, x, y, ratio);
			break;
		case DRAW_MODE::RIGHT:
			break;
		case DRAW_MODE::CENTER:
			neoNumberRenderer.draw(getRenderer(), number, x, y, ratio);
			break;
	}
}

void GameWindow::drawNumber(std::string number, int x, int y, float ratio, DRAW_MODE mode) {
	switch (mode) {
		case DRAW_MODE::LEFT:
			// neoNumberRenderer.drawLeft(getRenderer(), number, x, y, ratio);
			break;
		case DRAW_MODE::RIGHT:
			break;
		case DRAW_MODE::CENTER:
			neoNumberRenderer.draw(getRenderer(), number, x, y, ratio);
			break;
	}
}

void GameWindow::setColor(int color) {
	neoNumberRenderer.setColor(color);
}

int GameWindow::getNumberWidth(int number, float ratio) {
	return (neoNumberRenderer.getWidth(number, ratio));
}


int GameWindow::getNumberWidth(std::string number, float ratio) {
	return (neoNumberRenderer.getWidth(number, ratio));
}

int GameWindow::getNumberHeight(float ratio) {
	return (neoNumberRenderer.getHeight(ratio));
}

AnimatedTexture::AnimatedTexture() : texture(NULL), renderer(NULL), width(0), height(0), frameWidth(0), frameHeight(0), nbFramesPerLine(0), frameCount(0), currentFrame(0), frameTime(0), time(0) {}

AnimatedTexture::~AnimatedTexture() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void AnimatedTexture::init(SDL_Renderer *renderer, std::string path, int nbFramesPerLine, int frameCount, int frameTime) {
	this->renderer = renderer;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture) {
		std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	this->frameWidth = width / nbFramesPerLine;
	this->frameHeight = height / std::ceil(frameCount / static_cast<float>(nbFramesPerLine));
	this->nbFramesPerLine = nbFramesPerLine;
}

void AnimatedTexture::update(int deltaTime) {
	time += deltaTime;
	if (time >= frameTime) {
		time -= frameTime;
		currentFrame += 1;
		if (currentFrame >= frameCount) {
			currentFrame = 0;
		}
	}
}

void AnimatedTexture::render(SDL_Rect dstRect) {
	SDL_Rect srcRect = {frameWidth * (currentFrame % nbFramesPerLine), frameHeight * (currentFrame / nbFramesPerLine), frameWidth, frameHeight};
	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
} 