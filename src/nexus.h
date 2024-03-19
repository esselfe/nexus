#ifndef NEXUS_H
#define NEXUS_H 1

#include <time.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

extern char *nexus_version_string;
extern int verbose;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern unsigned int fps;
extern char *fps_text;

#endif /* NEXUS_H */
