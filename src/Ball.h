#ifndef BALL_H
#define BALL_H
#include "SDL2/SDL.h"
#include "PaddleHitType.h"

class Ball {
	public:
		Ball();
		void init(int x, int y);
		void move(double delta_time);
		void bounce_check(int screen_height, SDL_Rect left_paddle_rect, 
				SDL_Rect right_paddle_rect);
		void score_check(unsigned int &left_score, unsigned int &right_score, 
				int screen_width, int screen_height);
		void draw(SDL_Renderer* renderer) const;
	private:
		SDL_Rect ball_rect;
		paddle_hit_type paddle_last_hit = paddle_hit_type::none;
		double x_velocity;
		double y_velocity;
		void reset(int x, int y);
};

#endif
