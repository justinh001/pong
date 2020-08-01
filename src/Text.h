#ifndef TEXT_H
#define TEXT_h
#include <string>
#include "SDL2/SDL.h"

class Text {
	public:
		static void output(SDL_Renderer *renderer, const std::string &text, 
				int x, int y, int fontsize, Uint8 r, Uint8 g, Uint8 b);
};

#endif
