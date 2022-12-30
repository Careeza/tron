#include "neoNumberRenderer.hpp"
#include <string>
#include <iostream>

/*
0- 120
1- 100
2- 190
3- 190
4- 150
5- 190
6- 190
7- 140
8- 190
9- 180
*/

NeoNumberRenderer::NeoNumberRenderer() {
}

NeoNumberRenderer::~NeoNumberRenderer() {
}

void	NeoNumberRenderer::init(SDL_Renderer *renderer) {
	widths = {110, 90, 180, 180, 140, 180, 180, 130, 180, 170};
	for (int i = 0; i < 10; i++) {
		widthsTrandformed.push_back(widths[i] / RATIO);
	}
	height = 200;
	heightTransformed = height / RATIO;
	for (int i = 0; i < 10; i++) {
		std::string	path = "ressources/Blue/num/" + std::to_string(i) + ".png";
		textures.push_back(IMG_LoadTexture(renderer, path.c_str()));
	}
}

void	NeoNumberRenderer::draw(SDL_Renderer *renderer, int number, int x, int y) {
	x -= getWidth(number) / 2;
	std::string str = std::to_string(number);
	for (char c : str) {
		SDL_Rect rect = {x, y, widthsTrandformed[c - '0'], heightTransformed};
		SDL_Rect srcRect = {(200 - widths[c - '0']) / 2, 0, widths[c - '0'], height};
		SDL_RenderCopy(renderer, textures[c - '0'], &srcRect, &rect);
		x += widthsTrandformed[c - '0'];
	}
}

int		NeoNumberRenderer::getWidth(int number) {
	std::string str = std::to_string(number);
	int width = 0;
	for (char c : str) {
		width += widthsTrandformed[c - '0'];
	}
	return width;
}