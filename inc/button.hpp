#ifndef BUTTON_HPP

# define BUTTON_HPP

# include "render.hpp"

class Button {
public:
	Button(SDL_Renderer *renderer, SDL_Rect rect_, SDL_Texture *texture_);
	~Button();

	void		addOverTexture(SDL_Renderer *renderer, SDL_Texture *texture_);
	void		addOverTexture(SDL_Renderer *renderer, std::tuple<int, int, int, int> color);
	SDL_Texture	*getTexture();
	SDL_Texture	*getOverTexture();
	SDL_Rect&	getRect();
	void		setOver(bool over_);
	bool		isOver(int x, int y);
	bool 		getOver();
private:
	SDL_Rect		rect;
	SDL_Texture		*texture;
	bool			over;
	SDL_Texture		*overTexture;
};

#endif