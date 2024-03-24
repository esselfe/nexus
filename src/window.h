#ifndef WINDOW_H
#define WINDOW_H 1

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

extern SDL_Window *window;
extern SDL_GLContext context;
extern GLfloat winX, winY, winW, winH;

void WindowInit(void);

#endif /* WINDOW_H */