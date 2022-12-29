#include <unistd.h>
#include "game.hpp"
#include <SDL_mixer.h>

int		main(void) {
	Game	game;

	game.init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
		return 1;
	}

	Mix_Music *music = Mix_LoadMUS("ressources/gamePlay.mp3");
	if (!music)
	{
		fprintf(stderr, "Erreur lors du chargement de la musique: %s\n", Mix_GetError());
		return 1;
	}

	Mix_PlayMusic(music, -1);

	game.run();

	Mix_FreeMusic(music);
	Mix_CloseAudio();

	return (0);
}