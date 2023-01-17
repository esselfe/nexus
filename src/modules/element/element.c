#include <stdlib.h>

#include "nexus.h"

struct ElementList element_root_list;

void ElementInit(void) {
	int cnt;
	for (cnt = 0; cnt < 10; cnt ++) {
		ElementAdd();
	}
}

void ElementAdd(void) {
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

	elem->type = rand() % 5;
	elem->value = (rand() % 1000) + 1;
	elem->x = (rand() % 100) - 50;
	elem->y = 0.5;
	elem->z = (rand() % 100) - 50;
	elem->width = elem->value / 1000.0;
	elem->height = elem->value / 1000.0;
	elem->angle_x = 0.0;
	elem->angle_y = 0.0;
	elem->angle_z = 0.0;
}

void ElementListDestroy(void);

void ElementRemove(struct Element *elem);

