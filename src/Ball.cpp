#include "Ball.h"
#include <ctime>
#include <cstdlib>

Ball::Ball() {
	ball_rect.w = 10;
	ball_rect.h = 10;
}

void Ball::init(int x, int y) {
	reset(x, y);
}

void Ball::move(double delta_time) {
	ball_rect.x += x_velocity * delta_time;
	ball_rect.y += y_velocity * delta_time;
}

void Ball::bounce_check(int screen_height, SDL_Rect left_paddle_rect, 
		SDL_Rect right_paddle_rect) {
	if (ball_rect.y < 0 || ball_rect.y + ball_rect.h > screen_height) {
		y_velocity *= -1;
	}
	if (SDL_HasIntersection(&ball_rect, &left_paddle_rect) && 
			(paddle_last_hit == paddle_hit_type::none ||
			 paddle_last_hit == paddle_hit_type::right)) {
		x_velocity *= -1;
		paddle_last_hit = paddle_hit_type::left;
	}
	else if (SDL_HasIntersection(&ball_rect, &right_paddle_rect) &&
			(paddle_last_hit == paddle_hit_type::none ||
			 paddle_last_hit == paddle_hit_type::left)) {
		x_velocity *= -1;
		paddle_last_hit = paddle_hit_type::right;
	}
}

void Ball::score_check(unsigned int &left_score, unsigned int &right_score, 
		int screen_width, int screen_height) {
	if (ball_rect.x < 0) {
		right_score++;
		reset(screen_width / 2, screen_height / 2);
	}
	else if (ball_rect.x > screen_width) {
		left_score++;
		reset(screen_width / 2, screen_height / 2);
	}
}

void Ball::reset(int x, int y) {
	ball_rect.x = x - (ball_rect.w / 2);
	ball_rect.y = y - (ball_rect.h / 2);
	srand(time(0));
	y_velocity = rand() % 2 ? 100 : -100;
	if (paddle_last_hit == paddle_hit_type::none) {
		x_velocity = rand() % 2 ? 100 : -100;
	}
	else if (paddle_last_hit == paddle_hit_type::left) {
		x_velocity = 100;
	}
	else {
		x_velocity = -100;
	}
	paddle_last_hit = paddle_hit_type::none;
}

void Ball::draw(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white ball
	SDL_RenderFillRect(renderer, &ball_rect);
}
