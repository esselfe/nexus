#include <stdlib.h>
#include <sys/time.h>

#include "nexus.h"
#include "floor.h"
#include "render.h"
#include "element.h"

struct ElementList element_root_list;

char total_waste_text[128], total_battery_text[128],
	total_copper_text[128], total_gold_text[128], total_iron_text[128],
	total_magnet_text[128], total_rock_text[128], total_silver_text[128],
	total_wood_text[128];

void ElementInit(void) {
	if (verbose) printf("Initializing element\n");

	gettimeofday(&tv_score_saved, NULL);
	ElementScoreLoad();
	ElementTextureInit();
	ElementAdd(floor_factor*250);
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
		elem->type = rand() % 8;
		switch (elem->type) {
		case ELEMENT_TYPE_WASTE:
			elem->texture_id = texture_id_waste;
			elem->value = (rand() % 1000) + 100;
			break;
		case ELEMENT_TYPE_BATTERY:
			elem->texture_id = texture_id_battery;
			elem->value = 1;
			break;
		case ELEMENT_TYPE_COPPER:
			elem->texture_id = texture_id_copper;
			elem->value = (rand() % 100) + 100;
			break;
		case ELEMENT_TYPE_GOLD:
			elem->texture_id = texture_id_gold;
			elem->value = (rand() % 100) + 100;
			break;
		case ELEMENT_TYPE_IRON:
			elem->texture_id = texture_id_iron;
			elem->value = (rand() % 1000) + 100;
			break;
		case ELEMENT_TYPE_MAGNET:
			elem->texture_id = texture_id_magnet;
			elem->value = (rand() % 100) + 100;
			break;
		case ELEMENT_TYPE_ROCK:
			elem->texture_id = texture_id_rock;
			elem->value = (rand() % 1000) + 100;
			break;
		case ELEMENT_TYPE_SILVER:
			elem->texture_id = texture_id_silver;
			elem->value = (rand() % 100) + 100;
			break;
		case ELEMENT_TYPE_WOOD:
			elem->texture_id = texture_id_wood;
			elem->value = (rand() % 1000) + 100;
			break;
		}
		elem->x = rand() % ((int)floor_size + (int)(floor_size/2.0));
		elem->x = (rand() % 2) ? -elem->x : elem->x;
		elem->x += 100.0 + floor_center->x;
		elem->y = 100.0;
		elem->z = rand() % ((int)floor_size + (int)(floor_size/2.0));
		elem->z = (rand() % 2) ? -elem->z : elem->z;
		elem->z += 100.0 + floor_center->z;
		elem->width = 1.0;
		elem->height = 1.0;
		elem->angle_x = 0.0;
		elem->angle_y = 0.0;
		elem->angle_z = 0.0;
	}
	
	render = 1;
}

void ElementCleanArea(void) {
	if (element_root_list.first_element == NULL)
		return;
	
	struct Element *el = element_root_list.first_element, *el2;
	while (1) {
		if (el->y < 2.0 && 
		  (el->x < floor_root_list.first_floor->x - floor_size/2.0) ||
		  (el->x > floor_root_list.last_floor->x + floor_size/2.0) ||
		  (-el->z < floor_root_list.last_floor->z - floor_size/2.0) ||
		  (-el->z > floor_root_list.first_floor->z + floor_size/2.0)) {
			if (el->next != NULL) {
				el2 = el->next;
				ElementRemove(el);
				el = el2;
				continue;
			}
			else {
				ElementRemove(el);
				break;
			}
		}
		
		if (el->next != NULL)
			el = el->next;
		else
			break;
	}
}

void ElementListDestroy(void);

void ElementRemove(struct Element *elem) {
	render = 0;

	if (elem->prev != NULL && elem->next == NULL) {
		elem->prev->next = NULL;
		element_root_list.last_element = elem->prev;
	}
	else if (elem->prev == NULL && elem->next != NULL) {
		elem->next->prev = NULL;
		element_root_list.first_element = elem->next;
	}
	else if (elem->prev != NULL && elem->next != NULL) {
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
	}
	else if (elem->prev == NULL && elem->next == NULL) {
		element_root_list.last_element = NULL;
		element_root_list.first_element = NULL;
	}
	
	free(elem);
	--element_root_list.total_elements;
	
	render = 1;
}

