#ifndef GAME_H
#define GAME_H
#include "SDL2/SDL.h"
#include "Paddle.h"
#include "Ball.h"

class Game {
	public:
		bool running = true;
		Game(const char* title, unsigned int width, unsigned int height);
		~Game();
		void handle_events();
		void update();
		void render();
	private:
		SDL_Window *main_window = nullptr;
		SDL_Renderer *renderer = nullptr;
		SDL_Event input_event;
		Paddle left_paddle;
		Paddle right_paddle;
		Ball ball;
		int screen_width;
		int screen_height;
		Uint64 last = SDL_GetTicks();
		Uint64 now;
		double delta_time;
		bool fullscreen = false;
};

#endif
