#include "tools.hpp"

#include <SDL.h>
#include <SDL_render.h>
#include <random>

SDL_Texture* copyTexture(SDL_Renderer *renderer, SDL_Texture *textureToCopy) {
	if (!textureToCopy) {
		return (NULL);
	}
	
	int w, h;
	Uint32 format;
	SDL_QueryTexture(textureToCopy, &format, NULL, &w, &h);

	SDL_Texture *newTexture;
	newTexture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);

	SDL_SetRenderTarget(renderer, newTexture);
	SDL_RenderCopy(renderer, textureToCopy, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);

	return newTexture;
}


// La fonction rotateTexture prend en entrée un pointeur vers un renderer SDL,
// un pointeur vers une texture SDL à faire pivoter et un angle de rotation en degrés.
SDL_Texture*	rotateTexture(SDL_Renderer* renderer, SDL_Texture* textureSrc, double angle) {
	int				w, h;
	SDL_Texture		*texture(copyTexture(renderer, textureSrc));

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Point* center = new SDL_Point({ w / 2, h / 2 });
	SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, center, SDL_FLIP_NONE);

	delete center;
	return (texture);
}


int		getRandomNumber(int min, int max) {
	std::random_device rd;  // Utilise un générateur de nombres aléatoires de qualité supérieure s'il est disponible, sinon un générateur de qualité inférieure.
	std::mt19937 eng(rd());  // Initialise le générateur de nombres aléatoires avec une graine générée aléatoirement.
	std::uniform_int_distribution<> distr(min, max);  // Génère des nombres aléatoires entiers uniformément distribués entre min et max.
	return distr(eng);
}


void	drawRectBetweenPoints(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
	int x = x1 < x2 ? x1 : x2;
	int y = y1 < y2 ? y1 : y2;

	int width = abs(x2 - x1);
	int height = abs(y2 - y1);

	SDL_Rect rect = { x, y, width, height };

	SDL_RenderFillRect(renderer, &rect);
}

bool	collide(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x + rect1.w < rect2.x) {
		return false;
	}
	if (rect1.x > rect2.x + rect2.w) {
		return false;
	}
	if (rect1.y + rect1.h < rect2.y) {
		return false;
	}
	if (rect1.y > rect2.y + rect2.h) {
		return false;
	}
	return true;
}
