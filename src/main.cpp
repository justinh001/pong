#include "SDL2/SDL.h"
#include "Game.h"
#include <iostream>

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		Game game("Game Title", 960, 540);
		while (game.running) {
			game.handle_events();
			game.update();
			game.render();
		}
	}
	else {
		std::cerr << SDL_GetError() << std::endl;
	}
	return 0;
}
