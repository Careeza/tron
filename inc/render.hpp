#ifndef RENDER_HPP

# define RENDER_HPP

# include <SDL.h>
# include <SDL_image.h>
# include <tuple>

# define VIRTUAL_W 1920
# define VIRTUAL_H 1080

class GameWindow {
public:
	GameWindow();
	~GameWindow();
	void init();
	void update();
	void render();
	void clean();

	SDL_Renderer			*getRenderer();
	int						getWidth();
	int						getHeight();
	int						getHighDPI();
	float					getRatio();
	float					getRatioVirtual();
	std::tuple<int, int>	transformPosition(int x, int y);
	SDL_Texture				*getVirtualWindow();
private:
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*virtualWindow;
	SDL_Rect		virtualWindowRect;
	int				width;
	int				height;
	int				highDPI;
	float			ratio;
	float			ratioVirtual;
};

#endif