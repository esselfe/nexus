#include <unistd.h>
#include <pthread.h>

#include "nexus.h"

void *ElementThreadFunc(void *argp) {
	while (1) {
		printf("total: %lu\n", element_root_list.total_elements);
		if (element_root_list.total_elements < 5000)
			ElementAdd(2);
	
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

