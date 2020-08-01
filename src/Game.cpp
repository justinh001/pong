#include "Game.h"
#include "Text.h"
#include <iostream>

Game::Game(const char* title, unsigned int width, unsigned int height) : 
	left_paddle("Left paddle wins!"), right_paddle("Right paddle wins!") {
	main_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (main_window == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		running = false;
	}
	renderer = SDL_CreateRenderer(main_window, 
			-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		running = false;
	}
	SDL_GetWindowSize(main_window, &screen_width, &screen_height);
	left_paddle.init(screen_height / 2, screen_width / 4);
	right_paddle.init(screen_height / 2, (screen_width / 4) * 3);
	ball.init(screen_width / 2, screen_height / 2);
}

void Game::handle_events() {
	now = SDL_GetTicks();
	delta_time = (now - last) / 1000.0f;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&input_event);
	if (keys[SDL_SCANCODE_W]) {
		left_paddle.move(-1, delta_time, screen_height);
	}
	if (keys[SDL_SCANCODE_S]) {
		left_paddle.move(1, delta_time, screen_height);
	}
	if (keys[SDL_SCANCODE_UP]) {
		right_paddle.move(-1, delta_time, screen_height);
	}
	if (keys[SDL_SCANCODE_DOWN]) {
		right_paddle.move(1, delta_time, screen_height);
	}
	if (keys[SDL_SCANCODE_F11]) {
		if (fullscreen) {
			SDL_SetWindowFullscreen(main_window, 0);
		}
		else {
			SDL_SetWindowFullscreen(main_window, SDL_WINDOW_FULLSCREEN);
		}
		fullscreen = !fullscreen;
	}
	if (input_event.type == SDL_QUIT) {
		running = false;
	}
	last = now;
}

void Game::update() {
	ball.move(delta_time);
	ball.bounce_check(screen_height, left_paddle.get_rect(), right_paddle.get_rect());
	ball.score_check(left_paddle.get_score(), right_paddle.get_score(), 
			screen_width, screen_height);
	if (left_paddle.get_score() == 10) {
		left_paddle.win(renderer, screen_width / 2);
		running = false;
	}
	else if (right_paddle.get_score() == 10) {
		right_paddle.win(renderer, screen_width / 2);
		running = false;
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black background
	SDL_RenderClear(renderer);
	Text::output(renderer, std::to_string(left_paddle.get_score()), 
			(screen_width / 2) - 50, 0, 50, 255, 255, 255); //white text
	Text::output(renderer, std::to_string(right_paddle.get_score()), 
			(screen_width / 2) + 50, 0, 50, 255, 255, 255);
	ball.draw(renderer);
	left_paddle.draw(renderer);
	right_paddle.draw(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white middle separation line
	SDL_RenderDrawLine(renderer, screen_width / 2, 5, screen_width / 2, screen_height - 5);
	SDL_RenderPresent(renderer);
}

Game::~Game() {
	SDL_DestroyWindow(main_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
