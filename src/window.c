#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

#include "nexus.h"
#include "window.h"

SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;
// Window position and dimensions
GLfloat winX = 100.0, winY = 40.0, winW = 800.0, winH = 600.0;
char window_title[1024];

void WindowInit(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf ("nexus: SDL_Init() failed.\n");
		exit(1);
	}

	// Set OpenGL API version to 1.1 and show what we got
	int gl_major, gl_minor;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor);
	if (verbose) printf("Using OpenGL %d.%d\n", gl_major, gl_minor);

	sprintf(window_title, "nexus %s", nexus_version_string);
	window = SDL_CreateWindow(window_title, winX, winY, winW, winH,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		printf("nexus: Cannot create SDL2/GL context. Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		exit(1);
	}
}
