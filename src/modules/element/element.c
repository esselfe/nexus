#include <stdlib.h>
#include <sys/time.h>

#include "nexus.h"

struct ElementList element_root_list;

void ElementInit(void) {
	if (verbose) printf("Initializing element\n");

	gettimeofday(&tv_score_saved, NULL);
	ElementScoreLoad();
	ElementTextureInit();
	ElementAdd(floor_factor*60);
	ElementThreadStart();
	
	element_mat_amb_diff[0] = 0.4;
	element_mat_amb_diff[1] = 0.4;
	element_mat_amb_diff[2] = 0.4;
	element_mat_amb_diff[3] = 1.0;
}

void ElementAdd(unsigned int count) {
	render = 0;
	
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
		++element_root_list.total_elements;
		element_root_list.last_element = elem;
		elem->next = NULL;

		gettimeofday(&tv0, NULL);
		srand((unsigned int)tv0.tv_usec);
		elem->type = rand() % 5;
		switch (elem->type) {
		case ELEMENT_TYPE_WASTE:
			elem->texture_id = texture_id_waste;
			break;
		case ELEMENT_TYPE_IRON:
			elem->texture_id = texture_id_iron;
			break;
		case ELEMENT_TYPE_WOOD:
			elem->texture_id = texture_id_wood;
			break;
		case ELEMENT_TYPE_MAGNET:
			elem->texture_id = texture_id_magnet;
			break;
		case ELEMENT_TYPE_ROCK:
			elem->texture_id = texture_id_rock;
			break;
		}
		elem->value = (rand() % 1000) + 100;
		elem->x = rand() % (50*floor_factor);
		elem->x = (rand() % 2) ? -elem->x : elem->x;
		elem->x += 100.0;
		elem->y = 100.0;
		elem->z = rand() % (50*floor_factor);
		elem->z = (rand() % 2) ? -elem->z : elem->z;
		elem->z += 100.0;
		elem->width = elem->value / 1000.0;
		elem->height = elem->value / 1000.0;
		elem->angle_x = 0.0;
		elem->angle_y = 0.0;
		elem->angle_z = 0.0;
	}
	
	render = 1;
}

void ElementListDestroy(void);

void ElementRemove(struct Element *elem) {
	render = 0;

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
	
	render = 1;
}

