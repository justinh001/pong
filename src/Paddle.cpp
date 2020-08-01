#include "Paddle.h"
#include "Text.h"

Paddle::Paddle(std::string win_message) : win_message(win_message) {
	paddle_rect.h = 40;
	paddle_rect.w = 5;
}

void Paddle::init(int y, int x) {
	paddle_rect.y = y - (paddle_rect.h / 2);
	paddle_rect.x = x - (paddle_rect.w / 2);
}

void Paddle::win(SDL_Renderer *renderer, int x) const {
	Text::output(renderer, win_message, x, 50, 50, 255, 0, 0); //red game over text
	SDL_RenderPresent(renderer);
	SDL_Delay(2000); //2 seconds
}

void Paddle::draw(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white paddles
	SDL_RenderFillRect(renderer, &paddle_rect);
}

void Paddle::move(int change, double delta_time, int screen_height) {
	if (change < 0) { //move paddle up
		if (paddle_rect.y - border_buffer > 0) {
			paddle_rect.y += change * movement_speed * delta_time;
		}
	}
	if (change > 0) { //move paddle down
		if (paddle_rect.h + paddle_rect.y + border_buffer < screen_height) {
			paddle_rect.y += change * movement_speed * delta_time;
		}
	}
}
