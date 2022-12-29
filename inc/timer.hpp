#ifndef TIMER_HPP

# define TIMER_HPP


# include <SDL.h>
# include <SDL_timer.h>

class Timer
{
private:
	int startTicks;
	int pausedTicks;

	bool paused;
	bool started;

public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks();

	bool isStarted();
	bool isPaused();
};

#endif