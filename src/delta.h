#ifndef DELTA_H
#define DELTA_H 1

#include <time.h>
#include <sys/time.h>
#include <GL/gl.h>

extern GLfloat delta, delta_move;
extern time_t t0, tprev;
extern struct timeval tv0, tv_prev, tv_diff;

void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2);
void DeltaCompute(void);
void DeltaInit(void);
// Modules are supposed to associate this handler to their function
extern void (*DeltaFunc)(void);
void DeltaMove(void);

#endif /* DELTA_H */