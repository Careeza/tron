#include "neoNumberRenderer.hpp"
#include <string>
#include <iostream>

NeoNumberRenderer::NeoNumberRenderer() {
}

NeoNumberRenderer::~NeoNumberRenderer() {
}

void	NeoNumberRenderer::init(SDL_Renderer *renderer) {
	widths = {110, 90, 180, 180, 140, 180, 180, 130, 180, 170};
	height = 200;
	for (int i = 0; i < 10; i++) {
		std::string	path = "ressources/Blue/num/" + std::to_string(i) + ".png";
		textures.push_back(IMG_LoadTexture(renderer, path.c_str()));
	}
}

void	NeoNumberRenderer::draw(SDL_Renderer *renderer, int number, int x, int y, float ratio) {
	std::vector<int>	widthsTrandformed;
	int					heightTransformed;
	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / ratio);
	}
	heightTransformed = height / ratio;
	x -= getWidth(number, ratio) / 2;
	y -= heightTransformed / 2;
	std::string str = std::to_string(number);
	for (char c : str) {
		SDL_Rect rect = {x, y, widthsTrandformed[c - '0'], heightTransformed};
		SDL_Rect srcRect = {(200 - widths[c - '0']) / 2, 0, widths[c - '0'], height};
		SDL_RenderCopy(renderer, textures[c - '0'], &srcRect, &rect);
		x += widthsTrandformed[c - '0'];
	}
}

void	NeoNumberRenderer::draw(SDL_Renderer *renderer, std::string str, int x, int y, float ratio) {
	std::vector<int>	widthsTrandformed;
	int					heightTransformed;
	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / ratio);
	}
	heightTransformed = height / ratio;
	x -= getWidth(str, ratio) / 2;
	y -= heightTransformed / 2;
	for (char c : str) {
		SDL_Rect rect = {x, y, widthsTrandformed[c - '0'], heightTransformed};
		SDL_Rect srcRect = {(200 - widths[c - '0']) / 2, 0, widths[c - '0'], height};
		SDL_RenderCopy(renderer, textures[c - '0'], &srcRect, &rect);
		x += widthsTrandformed[c - '0'];
	}
}

void	NeoNumberRenderer::drawLeft(SDL_Renderer *renderer, int number, int x, int y, float ratio) {
	std::vector<int>	widthsTrandformed;
	int					heightTransformed;
	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / ratio);
	}
	heightTransformed = height / ratio;
	y -= heightTransformed / 2;
	std::string str = std::to_string(number);
	for (char c : str) {
		SDL_Rect rect = {x, y, widthsTrandformed[c - '0'], heightTransformed};
		SDL_Rect srcRect = {(200 - widths[c - '0']) / 2, 0, widths[c - '0'], height};
		SDL_RenderCopy(renderer, textures[c - '0'], &srcRect, &rect);
		x += widthsTrandformed[c - '0'];
	}
}

int		NeoNumberRenderer::getWidth(int number, float ratio) {
	std::vector<int>	widthsTrandformed;
	std::string str = std::to_string(number);

	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / ratio);
	}
	int width = 0;
	for (char c : str) {
		width += widthsTrandformed[c - '0'];
	}
	return width;
}

int		NeoNumberRenderer::getWidth(std::string str, float ratio) {
	std::vector<int>	widthsTrandformed;

	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / ratio);
	}
	int width = 0;
	for (char c : str) {
		width += widthsTrandformed[c - '0'];
	}
	return width;
}

int		NeoNumberRenderer::getHeight(float ratio) {
	return height / ratio;
}