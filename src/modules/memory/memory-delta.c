#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>

#include "nexus.h"
#include "delta.h"
#include "render.h"
#include "terminal.h"
#include "memory.h"

void MemoryDeltaCompute(void) {
	struct sysinfo si;
	sysinfo(&si);
	
	// Calculate the total memory in bytes
	memory_max = (GLfloat)(si.totalram * si.mem_unit);
	// Display the maximum memory as a text
	sprintf(memory_max_text, "%lu", (unsigned long)memory_max);

	// Calculate the used memory in bytes (total memory - free memory)
	GLfloat used_memory = si.totalram * si.mem_unit - si.freeram * si.mem_unit;
	// Scale the used memory to fit in a 3.0 units high meter
	memory_value = (3.0 / memory_max) * used_memory;
	// Display the used memory as a text, in bytes
	sprintf(memory_value_text, "%lu", (unsigned long)used_memory);

	// Same thing for swap
	swap_max = (GLfloat)(si.totalswap * si.mem_unit);
	sprintf(swap_max_text, "%lu", (unsigned long)swap_max);
	
	GLfloat used_swap = swap_max - (GLfloat)(si.freeswap * si.mem_unit);
	swap_value = (3.0/swap_max) * used_swap;
	sprintf(swap_value_text, "%lu", (unsigned long)used_swap);
	 

	// Once every second
	t0 = time(NULL);
	if (t0 - tprev > 0) {
		tprev = t0;
		sprintf(fps_text, "%u fps", fps);
		fps = 0;
	}
	else ++fps;

	// Once every half second
	gettimeofday(&tv0, NULL);
	tvdiff(&tv_prev, &tv0, &tv_diff);
	if (tv_diff.tv_sec >= 1 || tv_diff.tv_usec >= 500000) {
		tv_prev.tv_sec = tv0.tv_sec;
		tv_prev.tv_usec = tv0.tv_usec;
		terminal_cursor_blink = !terminal_cursor_blink;
	}
}

