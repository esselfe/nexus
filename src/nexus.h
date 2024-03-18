#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

#include "selectID.h"

////////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////////

// nexus.c
////////////////////////////////
extern char *nexus_version_string;
extern int verbose;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern unsigned int fps;
extern char *fps_text;

extern time_t t0, tprev;
extern struct timeval tv0, tv_prev, tv_diff;
void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2);

////////////////////////////////////////////////////////////////
// Modules
////////////////////////////////////////////////////////////////

// Driving
////////////////////////////////
void DrivingDelta(void);
void DrivingEvent(void);
void DrivingRender(void);

#endif /* NEXUS_H */
