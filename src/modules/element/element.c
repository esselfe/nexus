#include <stdlib.h>

#include "nexus.h"

unsigned long long total_waste, total_iron, total_wood,
	total_magnet, total_rock;
struct ElementList element_root_list;

void ElementInit(void) {
	ElementScoreLoad();
	ElementAdd(10);
}

void ElementAdd(unsigned int count) {
	unsigned int cnt;
	for (cnt = 0; cnt < count; cnt++) {
		struct Element *elem = malloc(sizeof(struct Element));

		if (element_root_list.first_element == NULL) {
			element_root_list.first_element = elem;
			elem->prev = NULL;
		}
		else {
			element_root_list.last_element->next = elem;
			elem->prev = element_root_list.last_element;
		}
		element_root_list.last_element = elem;
		elem->next = NULL;

		gettimeofday(&tv0, NULL);
		srand((unsigned int)tv0.tv_usec);
		elem->type = rand() % 5;
		elem->value = (rand() % 1000) + 100;
		elem->x = (rand() % 100) - 50;
		elem->y = 0.5;
		elem->z = (rand() % 100) - 50;
		elem->width = elem->value / 1000.0;
		elem->height = elem->value / 1000.0;
		elem->angle_x = 0.0;
		elem->angle_y = 0.0;
		elem->angle_z = 0.0;
	}
}

void ElementListDestroy(void);

void ElementRemove(struct Element *elem) {
	if (elem->next == NULL && elem->prev != NULL) {
		elem->prev->next = NULL;
		element_root_list.last_element = elem->prev;
	}
	else if (elem->next != NULL && elem->prev == NULL) {
		elem->next->prev = NULL;
		element_root_list.first_element = elem->next;
	}
	else if (elem->prev != NULL && elem->next != NULL) {
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
	}

	free(elem);
	--element_root_list.total_elements;
}

