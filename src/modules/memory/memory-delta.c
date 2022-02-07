#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#include "nexus.h"

void MemoryDeltaCompute(void) {
	struct sysinfo si;
	sysinfo(&si);
	
	memory_max = (GLfloat)(si.totalram * si.mem_unit);
	 sprintf(memory_max_text, "%lu", (unsigned long)memory_max);
	memory_value = (3.0/memory_max) * (memory_max - (si.freeram * si.mem_unit));
	 sprintf(memory_value_text, "%lu", (unsigned long)(memory_value * 1000000000.0));
	
	swap_max = (GLfloat)(si.totalswap * si.mem_unit);
	 sprintf(swap_max_text, "%lu", (unsigned long)swap_max);
	swap_value = (3.0/swap_max) * (swap_max - (si.freeswap * si.mem_unit));
	 sprintf(swap_value_text, "%lu", (unsigned long)(swap_value * 1000000000.0));
	 

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
}

