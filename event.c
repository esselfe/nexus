#include <SDL2/SDL.h>

#include "nexus.h"

SDL_Event event;

void EventCheck(void) {
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			mainloopend = 1;
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_q:
				mainloopend = 1;
				break;
			default:
				break;
			}
		}
	}
}

