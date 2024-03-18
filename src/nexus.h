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

// Memory
////////////////////////////////
extern GLfloat memory_max, memory_value;
extern char memory_max_text[128], memory_value_text[128];
extern GLfloat swap_max, swap_value;
extern char swap_max_text[128], swap_value_text[128];
extern GLfloat memory_mat_amb_diff[4];
void MemoryDeltaCompute(void);
void MemoryInit(void);
void MemoryRender(void);

#endif /* NEXUS_H */
