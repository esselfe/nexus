#include <unistd.h>
#include <pthread.h>

#include "nexus.h"
#include "floor.h"
#include "mode.h"
#include "element.h"

void *ElementThreadFunc(void *argp) {
	int element_max = 500 * floor_factor;
	if (element_max > 5000)
		element_max = 5000;
	while (1) {
		if (element_root_list.total_elements < element_max &&
		  ModeGet() == MODE_ELEMENT)
			ElementAdd(1);
	
		sleep(5);
	}
	
	return NULL;
}

void ElementThreadStart(void) {
	pthread_t thr;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thr, &attr, ElementThreadFunc, NULL);
	pthread_detach(thr);
	pthread_attr_destroy(&attr);
}

