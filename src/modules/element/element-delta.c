#include <sys/time.h>

#include "nexus.h"

void ElementCheckCollision(void) {
	if (element_root_list.first_element == NULL)
		return;

	struct Element *el = element_root_list.first_element;
	while (1) {
		if (cam.x > el->x - 1.5 &&
			cam.x < el->x + 1.5) {
			if (cam.z > el->z - 1.5 &&
				cam.z < el->z + 1.5) {
				if (el->type == ELEMENT_TYPE_WASTE)
					total_waste += el->value;
				else if (el->type == ELEMENT_TYPE_IRON)
					total_iron += el->value;
				else if (el->type == ELEMENT_TYPE_WOOD)
					total_wood += el->value;
				else if (el->type == ELEMENT_TYPE_MAGNET)
					total_magnet += el->value;
				else if (el->type == ELEMENT_TYPE_ROCK)
					total_rock += el->value;

				ElementRemove(el);
				ElementAdd(2);
			}
		}

		if (el == NULL)
			break;

		if (el->next == NULL)
			break;
		else
			el = el->next;
	}
}

void ElementMoveFlying(void) {
	struct Element *el = element_root_list.first_element;
	if (el == NULL)
		return;
	
	while (1) {
		if (el->y > 1.0) {
			if (el->y < 2.5) {
				el->x -= 0.1;
				el->y -= 0.1;
				el->z -= 0.1;
			}
			else {
				el->x -= delta_move;
				el->y -= delta_move;
				el->z -= delta_move;
			}
		}
		
		if (el->next == NULL)
			break;
		else
			el = el->next;
	}
}

void ElementDelta(void) {
	gettimeofday(&tv0, NULL);
	
	tvdiff(&tv_prev, &tv0, &tv_diff);
	if (tv_diff.tv_sec > 0 || tv_diff.tv_usec > 250000) {
		ElementCheckCollision();
	}

	tvdiff(&tv_score_saved, &tv0, &tv_diff);
	if (tv_diff.tv_sec > 30) {
		ElementScoreSave();
		tv_score_saved.tv_sec = tv0.tv_sec;
		tv_score_saved.tv_usec = tv0.tv_usec;
	}
	
	DeltaMove();
	
	ElementMoveFlying();

	delta += delta_move;
	if (delta >= 360.0)
		delta -= 360.0;
}

