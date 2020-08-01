#ifndef PADDLE_H
#define PADDLE_H
#include "SDL2/SDL.h"
#include <string>

class Paddle {
	public:
		inline unsigned int &get_score() { return score; }
		inline SDL_Rect get_rect() const { return paddle_rect; }
		Paddle(std::string win_message);
		void init(int y, int x);
		void win(SDL_Renderer* renderer, int x) const;
		void draw(SDL_Renderer* renderer) const;
		void move(int change, double delta_time, int screen_height);
	private:
		SDL_Rect paddle_rect;
		const int border_buffer = 10;
		const int movement_speed = 200;
		std::string win_message;
		unsigned int score = 0;
};

#endif
