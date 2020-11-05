#include <iostream>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "Text.h"

void Text::output(SDL_Renderer *renderer, const std::string &text, 
		int x, int y, int fontsize, Uint8 r, Uint8 g, Uint8 b) {
	TTF_Init();
	TTF_Font *Sans = TTF_OpenFont("fonts/OpenSans-Regular.ttf", fontsize);
	if (!Sans) {
		std::cerr << TTF_GetError() << std::endl;
	}
	const SDL_Color Color = {r, g, b, 255};
	SDL_Surface *temp_surface = TTF_RenderText_Solid(Sans, text.c_str(), Color);
	TTF_CloseFont(Sans);
	if (!temp_surface) {
		std::cerr << SDL_GetError() << std::endl;
	}
	SDL_Texture *message_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	if (!message_texture) {
		std::cerr << SDL_GetError() << std::endl;
	}
	SDL_Rect dest_rect;
	dest_rect.w = temp_surface->w;
	dest_rect.h = temp_surface->h;
	dest_rect.x = x - (dest_rect.w / 2);
	dest_rect.y = y;
	SDL_FreeSurface(temp_surface);
	SDL_RenderCopy(renderer, message_texture, NULL, &dest_rect);
	SDL_DestroyTexture(message_texture);
	TTF_Quit();
}
