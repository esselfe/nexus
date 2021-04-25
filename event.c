#include <SDL2/SDL.h>

#include "nexus.h"

SDL_Event event;

void EventCheck(void) {
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			mainloopend = 1;
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				mainloopend = 1;
				break;
			case SDLK_UP:
				//flagZ -= 0.5;
				cam.z -= 1.0;
				cam.lz -= 1.0;
				break;
			case SDLK_DOWN:
				//flagZ += 0.5;
				cam.z += 1.0;
				cam.lz += 1.0;
				break;
			case SDLK_LEFT:
				//flagX -= 0.5;
				cam.x -= 1.0;
				cam.lx -= 1.0;
				break;
			case SDLK_RIGHT:
				//flagX += 0.5;
				cam.x += 1.0;
				cam.lx += 1.0;
				break;
			case SDLK_PAGEUP:
				//flagY += 0.5;
				cam.y += 1.0;
				cam.ly += 1.0;
				break;
			case SDLK_PAGEDOWN:
				//flagY -= 0.5;
				cam.y -= 1.0;
				cam.ly -= 1.0;
				break;
			case SDLK_b:
				if (state != STATE_BROWSER)
					StateSet(STATE_BROWSER);
				else
					StateSet(state_prev);
				break;
			case SDLK_e:
				if (state != STATE_EDITOR)
					StateSet(STATE_EDITOR);
				else
					StateSet(state_prev);
				break;
			case SDLK_m:
				if (state != STATE_MEMORY)
					StateSet(STATE_MEMORY);
				else
					StateSet(state_prev);
				break;
			default:
				break;
			}
		}
	}
}

