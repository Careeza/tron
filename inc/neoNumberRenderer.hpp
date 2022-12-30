#ifndef NEO_NUMBER_RENDERER_HPP

# define NEO_NUMBER_RENDERER_HPP

# include <SDL.h>
# include <SDL_image.h>
# include <vector>

# define RATIO 5

class NeoNumberRenderer {
	public:
		NeoNumberRenderer();
		~NeoNumberRenderer();
		void	init(SDL_Renderer *renderer);
		void	draw(SDL_Renderer *renderer, int number, int x, int y);
		int		getWidth(int number);
	private:
		std::vector<SDL_Texture*>	textures;
		std::vector<int>			widths;
		std::vector<int>			widthsTrandformed;
		int							height;
		int							heightTransformed;
};

#endif