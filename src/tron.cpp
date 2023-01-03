#include <unistd.h>
#include "game.hpp"
#include <SDL_mixer.h>

int		main(void) {
	Game	game;

	game.init();
	game.run();

	// Mix_FreeMusic(music);
	// Mix_CloseAudio();

	return (0);
}