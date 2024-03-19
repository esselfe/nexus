#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "nexus.h"
#include "delta.h"
#include "flag.h"
#include "terminal.h"

// Modules have to assiociate this function pointer to their handler
void (*DeltaFunc)(void);

GLfloat delta, delta_move;
time_t t0, tprev;
struct timeval tv0, tv_prev, tv_diff;
struct timeval tv_prev_frame;

// Calculate the difference between 2 timings like 0.223880 and 0.384859
void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2) {
	tv_diff2->tv_sec = tv_end->tv_sec - tv_start->tv_sec;
	
	if (tv_start->tv_sec == tv_end->tv_sec) {
		tv_diff2->tv_usec = tv_end->tv_usec - tv_start->tv_usec;
	}
	else {
		tv_diff2->tv_usec = tv_end->tv_usec + (1000000-tv_start->tv_usec);
		if (tv_diff2->tv_usec >= 1000000) {
			++tv_diff2->tv_sec;
			tv_diff2->tv_usec -= 1000000;
		}
		if (tv_diff2->tv_sec > 0)
			--tv_diff2->tv_sec;
	}
}

void DeltaInit(void) {
	if (verbose) printf("Initializing delta\n");
	DeltaFunc = DeltaCompute;
	tprev = time(NULL);
	gettimeofday(&tv_prev, NULL);
	tv_prev_frame.tv_sec = tv_prev.tv_sec;
	tv_prev_frame.tv_usec = tv_prev.tv_usec;
}

void DeltaCompute(void) {
	gettimeofday(&tv0, NULL);
	
	// Once every second
	t0 = (time_t)tv0.tv_sec;
	if (t0 - tprev > 0) {
		tprev = t0;
		sprintf(fps_text, "%u fps", fps);
		fps = 0;
	}

	// Once every half second
	tvdiff(&tv_prev, &tv0, &tv_diff);
	if (tv_diff.tv_sec >= 1 || tv_diff.tv_usec >= 500000) {
		tv_prev.tv_sec = tv0.tv_sec;
		tv_prev.tv_usec = tv0.tv_usec;
		terminal_cursor_blink = !terminal_cursor_blink;
	}

	DeltaMove();

	// Once every frame
	delta += delta_move;
	if (delta >= 360.0)
		delta -= 360.0;

	FlagUpdate();
}

void DeltaMove(void) {
	tvdiff(&tv_prev_frame, &tv0, &tv_diff);
	tv_prev_frame.tv_sec = tv0.tv_sec;
	tv_prev_frame.tv_usec = tv0.tv_usec;
	delta_move = ((GLfloat)tv_diff.tv_sec +
		(GLfloat)tv_diff.tv_usec/1000000) * 60.0;
}

