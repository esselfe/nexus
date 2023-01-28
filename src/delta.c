#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "nexus.h"

void (*DeltaFunc)(void);

GLfloat delta_move;
struct timeval tv_prev_frame;

void DeltaInit(void) {
	gettimeofday(&tv_prev_frame, NULL);
}

void DeltaCompute(void) {
	// Once every second
	t0 = time(NULL);
	if (t0 - tprev > 0) {
		tprev = t0;
		sprintf(fps_text, "%u fps", fps);
		fps = 0;
	}

	// Once every half second
	gettimeofday(&tv0, NULL);
	tvdiff(&tv_prev, &tv0, &tv_diff);
	if (tv_diff.tv_sec >= 1 || tv_diff.tv_usec >= 500000) {
		tv_prev.tv_sec = tv0.tv_sec;
		tv_prev.tv_usec = tv0.tv_usec;
		terminal_cursor_blink = !terminal_cursor_blink;
	}

	DeltaMove();

	// Once every frame
	delta += delta_move; //1.0;
	if (delta >= 360.0)
		delta -= 360.0;

	FlagUpdate();
}

void DeltaMove(void) {
	tvdiff(&tv_prev_frame, &tv0, &tv_diff);
	tv_prev_frame.tv_sec = tv0.tv_sec;
	tv_prev_frame.tv_usec = tv0.tv_usec;
	delta_move = ((GLfloat)tv_diff.tv_sec +
		(GLfloat)tv_diff.tv_usec/1000000) * 50.0;
}

