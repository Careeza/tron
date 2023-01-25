#ifndef TOOLS_HPP

# define TOOLS_HPP

# include <SDL.h>
# include <vector>

SDL_Texture*		copyTexture(SDL_Renderer *renderer, SDL_Texture *textureToCopy);
SDL_Texture*		rotateTexture(SDL_Renderer* renderer, SDL_Texture* textureSrc, double angle);
int					getRandomNumber(int min, int max);
std::vector<int>	getRandomNumbers(int n, int min = 0, int max = 9);

void						drawRectBetweenPoints(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
bool						collide(SDL_Rect rect1, SDL_Rect rect2);
std::vector<std::string>	split(const std::string &s, char delim);

#endif