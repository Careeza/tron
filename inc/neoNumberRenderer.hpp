#ifndef NEO_NUMBER_RENDERER_HPP

# define NEO_NUMBER_RENDERER_HPP

# include <SDL.h>
# include <SDL_image.h>
# include <vector>
# include <string>

class NeoNumberRenderer {
	public:
		NeoNumberRenderer();
		~NeoNumberRenderer();
		void	init(SDL_Renderer *renderer);
		void	setColor(int color);
		void	draw(SDL_Renderer *renderer, int number, int x, int y, float ratio);
		void	drawLeft(SDL_Renderer *renderer, int number, int x, int y, float ratio);
		void	draw(SDL_Renderer *renderer, std::string number, int x, int y, float ratio);
		int		getWidth(int number, float ratio);
		int		getWidth(std::string number, float ratio);
		int		getHeight(float ratio);
	private:
		int										color;
		std::vector<std::vector<SDL_Texture*>>	textures;
		std::vector<int>						widths;
		int										height;
};

#endif