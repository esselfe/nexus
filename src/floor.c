#include <stdlib.h>
#include <GL/gl.h>

#include "nexus.h"
#include "floor.h"
#include "image.h"

int floor_freeze;
int floor_factor;
GLfloat floor_size;
GLuint floor_texture_id;
static GLfloat floor_mat_amb_diff[4];
struct FloorList floor_root_list;
struct Floor *floor_center;

void FloorTextureSetup(GLuint *id, unsigned int width, unsigned int height,
	  char *filename) {
	GLubyte *data = ImageFromPNGFile(width, height, filename);
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void FloorInit(void) {
	if (verbose) printf("Initializing floor\n");
	
	if (floor_factor <= 0)
		floor_factor = 4;
	else if (floor_factor > 100)
		floor_factor = 100;
	
	floor_size = 100.0 * floor_factor;
	
	FloorTextureSetup(&floor_texture_id, 640, 640, "images/floor01-640.png");
	
	floor_mat_amb_diff[0] = 0.4;
	floor_mat_amb_diff[1] = 0.4;
	floor_mat_amb_diff[2] = 0.4;
	floor_mat_amb_diff[3] = 1.0;
	
	// northwest
	struct Floor *fl = malloc(sizeof(struct Floor));
	floor_root_list.first_floor = fl;
	fl->prev = NULL;
	fl->offset_x = -1;
	fl->offset_z = 1;
	fl->x = -floor_size;
	fl->y = 0.0;
	fl->z = floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// north
	fl->offset_x = 0;
	fl->offset_z = 1;
	fl->x = 0.0;
	fl->y = 0.0;
	fl->z = floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// northeast
	fl->offset_x = 1;
	fl->offset_z = 1;
	fl->x = floor_size;
	fl->y = 0.0;
	fl->z = floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// centerwest
	fl->offset_x = -1;
	fl->offset_z = 0;
	fl->x = -floor_size;
	fl->y = 0.0;
	fl->z = 0.0;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// center
	floor_center = fl;
	fl->offset_x = 0;
	fl->offset_z = 0;
	fl->x = 0.0;
	fl->y = 0.0;
	fl->z = 0.0;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// centereast
	fl->offset_x = 1;
	fl->offset_z = 0;
	fl->x = floor_size;
	fl->y = 0.0;
	fl->z = 0.0;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// southwest
	fl->offset_x = -1;
	fl->offset_z = -1;
	fl->x = -floor_size;
	fl->y = 0.0;
	fl->z = -floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// south
	fl->offset_x = 0;
	fl->offset_z = -1;
	fl->x = 0.0;
	fl->y = 0.0;
	fl->z = -floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// southeast
	fl->offset_x = 1;
	fl->offset_z = -1;
	fl->x = floor_size;
	fl->y = 0.0;
	fl->z = -floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = NULL;
	
	floor_root_list.last_floor = fl;
}

void FloorRender(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_BLEND);
	if (daylight_amount > 0.4) {
		floor_mat_amb_diff[0] = daylight_amount;
		floor_mat_amb_diff[1] = daylight_amount;
		floor_mat_amb_diff[2] = daylight_amount;
		floor_mat_amb_diff[3] = 1.0;
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            floor_mat_amb_diff);
	
	struct Floor *fl = floor_root_list.first_floor;
	while (1) {
		glPushMatrix();
		glTranslatef(fl->x, fl->y, -fl->z);
		glBindTexture(GL_TEXTURE_2D, fl->texture_id);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		 glVertex3f(-floor_size/2.0, 0.0, floor_size/2.0);
		glTexCoord2f(0.0, 10.0*floor_factor);
		 glVertex3f(floor_size/2.0, 0.0, floor_size/2.0);
		glTexCoord2f(10.0*floor_factor, 10.0*floor_factor);
		 glVertex3f(floor_size/2.0, 0.0, -floor_size/2.0);
		glTexCoord2f(10.0*floor_factor, 0.0);
		 glVertex3f(-floor_size/2.0, 0.0, -floor_size/2.0);
		glTexCoord2f(0.0, 0.0);
		 glVertex3f(-floor_size/2.0, 0.0, floor_size/2.0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_LINES);
		 glColor3f(0.6, 0.7, 0.8);
		 glVertex3f(-floor_size/2.0, 0.0, floor_size/2.0);
		 glVertex3f(-floor_size/2.0, 1.0, floor_size/2.0);
		 glVertex3f(-floor_size/2.0, 0.0, -floor_size/2.0);
		 glVertex3f(-floor_size/2.0, 1.0, -floor_size/2.0);
		 glVertex3f(floor_size/2.0, 0.0, -floor_size/2.0);
		 glVertex3f(floor_size/2.0, 1.0, -floor_size/2.0);
		 glVertex3f(floor_size/2.0, 0.0, floor_size/2.0);
		 glVertex3f(floor_size/2.0, 1.0, floor_size/2.0);
		glEnd();
		glPopMatrix();
		
		if (fl->next != NULL)
			fl = fl->next;
		else
			break;
	}
}

void FloorAddNorthRow(void) {
	struct Floor *fl1 = malloc(sizeof(struct Floor)),
		*fl2 = malloc(sizeof(struct Floor)),
		*fl3 = malloc(sizeof(struct Floor));
	
	// Add north row
	////////////////
	
	// northwest
	fl1->prev = NULL;
	fl1->next = fl2;
	fl1->offset_x = floor_root_list.first_floor->offset_x;
	fl1->offset_z = floor_root_list.first_floor->offset_z + 1;
	fl1->x = floor_size * fl1->offset_x;
	fl1->y = 0.0;
	fl1->z = floor_size * fl1->offset_z;
	fl1->texture_id = floor_texture_id;
	
	// north
	fl2->prev = fl1;
	fl2->next = fl3;
	fl2->offset_x = floor_root_list.first_floor->next->offset_x;
	fl2->offset_z = floor_root_list.first_floor->next->offset_z + 1;
	fl2->x = floor_size * fl2->offset_x;
	fl2->y = 0.0;
	fl2->z = floor_size * fl2->offset_z;
	fl2->texture_id = floor_texture_id;
	
	// northeast
	fl3->prev = fl2;
	fl3->next = floor_root_list.first_floor;
	floor_root_list.first_floor->prev = fl3;
	fl3->offset_x = floor_root_list.first_floor->next->next->offset_x;
	fl3->offset_z = floor_root_list.first_floor->next->next->offset_z + 1;
	fl3->x = floor_size * fl3->offset_x;
	fl3->y = 0.0;
	fl3->z = floor_size * fl3->offset_z;
	fl3->texture_id = floor_texture_id;
	
	floor_center = floor_root_list.first_floor->next;
	floor_root_list.first_floor = fl1;
	
	// Remove south row
	///////////////////
	
	fl3 = floor_root_list.last_floor;
	fl2 = fl3->prev;
	fl1 = fl2->prev;
	floor_root_list.last_floor = fl1->prev;
	fl1->prev->next = NULL;
	free(fl3);
	free(fl2);
	free(fl1);
	
	if (ModeGet() == MODE_ELEMENT)
		ElementCleanArea();
}

void FloorAddSouthRow(void) {
	struct Floor *fl1 = malloc(sizeof(struct Floor)),
		*fl2 = malloc(sizeof(struct Floor)),
		*fl3 = malloc(sizeof(struct Floor));
	
	// Add south row
	////////////////
	
	// southwest
	fl1->prev = floor_root_list.last_floor;
	fl1->next = fl2;
	fl1->offset_x = floor_root_list.last_floor->prev->prev->offset_x;
	fl1->offset_z = floor_root_list.last_floor->prev->prev->offset_z - 1;
	fl1->x = floor_size * fl1->offset_x;
	fl1->y = 0.0;
	fl1->z = floor_size * fl1->offset_z;
	fl1->texture_id = floor_texture_id;
	
	// south
	fl2->prev = fl1;
	fl2->next = fl3;
	fl2->offset_x = floor_root_list.last_floor->prev->offset_x;
	fl2->offset_z = floor_root_list.last_floor->prev->offset_z - 1;
	fl2->x = floor_size * fl2->offset_x;
	fl2->y = 0.0;
	fl2->z = floor_size * fl2->offset_z;
	fl2->texture_id = floor_texture_id;
	
	// southeast
	fl3->prev = fl2;
	fl3->next = NULL;
	floor_root_list.last_floor->next = fl1;
	fl3->offset_x = floor_root_list.last_floor->offset_x;
	fl3->offset_z = floor_root_list.last_floor->offset_z - 1;
	fl3->x = floor_size * fl3->offset_x;
	fl3->y = 0.0;
	fl3->z = floor_size * fl3->offset_z;
	fl3->texture_id = floor_texture_id;
	
	floor_center = floor_root_list.last_floor->prev;
	floor_root_list.last_floor->next = fl1;
	floor_root_list.last_floor = fl3;
	
	// Remove north row
	///////////////////
	
	fl1 = floor_root_list.first_floor;
	fl2 = fl1->next;
	fl3 = fl2->next;
	floor_root_list.first_floor = fl3->next;
	fl3->next->prev = NULL;
	free(fl1);
	free(fl2);
	free(fl3);
	
	if (ModeGet() == MODE_ELEMENT)
		ElementCleanArea();
}

void FloorAddWestRow(void) {
	struct Floor *fl1 = malloc(sizeof(struct Floor)),
		*fl2 = malloc(sizeof(struct Floor)),
		*fl3 = malloc(sizeof(struct Floor));
	
	// Add west row
	////////////////
	
	// northwest
	fl1->prev = NULL;
	fl1->next = floor_root_list.first_floor;
	floor_root_list.first_floor->prev = fl1;
	fl1->offset_x = floor_root_list.first_floor->offset_x - 1;
	fl1->offset_z = floor_center->offset_z + 1;
	fl1->x = floor_size * fl1->offset_x;
	fl1->y = 0.0;
	fl1->z = floor_size * fl1->offset_z;
	fl1->texture_id = floor_texture_id;
	
	// centerwest
	fl2->prev = fl1->next->next->next;
	fl1->next->next->next->next = fl2;
	fl2->next = floor_center->prev;
	floor_center->prev->prev = fl2;
	fl2->offset_x = fl1->offset_x;
	fl2->offset_z = floor_center->offset_z;
	fl2->x = floor_size * fl2->offset_x;
	fl2->y = 0.0;
	fl2->z = floor_size * fl2->offset_z;
	fl2->texture_id = floor_texture_id;
	
	// southwest
	fl3->prev = floor_center->next;
	floor_center->next->next = fl3;
	floor_root_list.last_floor->prev->prev->prev = fl3;
	fl3->next = floor_root_list.last_floor->prev->prev;
	floor_root_list.last_floor->prev->prev->prev = fl3;
	fl3->offset_x = fl2->offset_x;
	fl3->offset_z = floor_center->offset_z - 1;
	fl3->x = floor_size * fl3->offset_x;
	fl3->y = 0.0;
	fl3->z = floor_size * fl3->offset_z;
	fl3->texture_id = floor_texture_id;
	
	floor_center = floor_center->prev;
	floor_root_list.first_floor = fl1;
	
	// Remove east row
	///////////////////
	
	fl1 = floor_center->prev->prev;
	fl1->prev->next = fl1->next;
	fl1->next->prev = fl1->prev;
	fl2 = floor_center->next->next;
	fl2->prev->next = fl2->next;
	fl2->next->prev = fl2->prev;
	fl3 = floor_root_list.last_floor;
	fl3->prev->next = NULL;
	floor_root_list.last_floor = fl3->prev;
	free(fl1);
	free(fl2);
	free(fl3);
	
	if (ModeGet() == MODE_ELEMENT)
		ElementCleanArea();
}

void FloorAddEastRow(void) {
	struct Floor *fl1 = malloc(sizeof(struct Floor)),
		*fl2 = malloc(sizeof(struct Floor)),
		*fl3 = malloc(sizeof(struct Floor));
	
	// Add east row
	////////////////
	
	// northeast
	fl1->prev = floor_root_list.first_floor->next->next;
	fl1->prev->next = fl1;
	fl1->next = floor_center->prev;
	fl1->next->prev = fl1;
	fl1->offset_x = fl1->prev->offset_x + 1;
	fl1->offset_z = fl1->prev->offset_z;
	fl1->x = floor_size * fl1->offset_x;
	fl1->y = 0.0;
	fl1->z = floor_size * fl1->offset_z;
	fl1->texture_id = floor_texture_id;
	
	// centereast
	fl2->prev = floor_center->next;
	fl2->next = floor_center->next->next;
	floor_center->next->next->prev = fl2;
	floor_center->next->next = fl2;
	fl2->offset_x = fl1->offset_x;
	fl2->offset_z = floor_center->offset_z;
	fl2->x = floor_size * fl2->offset_x;
	fl2->y = 0.0;
	fl2->z = floor_size * fl2->offset_z;
	fl2->texture_id = floor_texture_id;
	
	// southeast
	fl3->prev = floor_root_list.last_floor;
	floor_root_list.last_floor->next = fl3;
	fl3->next = NULL;
	fl3->offset_x = fl2->offset_x;
	fl3->offset_z = floor_center->offset_z - 1;
	fl3->x = floor_size * fl3->offset_x;
	fl3->y = 0.0;
	fl3->z = floor_size * fl3->offset_z;
	fl3->texture_id = floor_texture_id;
	
	floor_center = floor_center->next;
	floor_root_list.last_floor = fl3;
	
	// Remove west row
	///////////////////
	
	fl1 = floor_root_list.first_floor;
	floor_root_list.first_floor = fl1->next;
	fl1->next->prev = NULL;
	fl2 = floor_center->prev->prev;
	fl2->prev->next = fl2->next;
	fl2->next->prev = fl2->prev;
	fl3 = floor_root_list.last_floor->prev->prev->prev;
	fl3->prev->next = fl3->next;
	fl3->next->prev = fl3->prev;
	free(fl1);
	free(fl2);
	free(fl3);
	
	if (ModeGet() == MODE_ELEMENT)
		ElementCleanArea();
}

// Used when changing floor factor via the terminal
void FloorResetSize(void) {
	struct Floor *fl = floor_root_list.first_floor;
	int cnt = 1;
	while (1) {
		if (cnt == 1) {
			fl->x = floor_center->x - floor_size;
			fl->z = floor_center->z + floor_size;
		}
		else if (cnt == 2) {
			fl->x = floor_center->x;
			fl->z = floor_center->z + floor_size;
		}
		else if (cnt == 3) {
			fl->x = floor_center->x + floor_size;
			fl->z = floor_center->z + floor_size;
		}
		else if (cnt == 4) {
			fl->x = floor_center->x - floor_size;
			fl->z = floor_center->z;
		}
		// center doesn't move
		//else if (cnt == 5) {
			//fl->x = floor_center->x;
			//fl->z = floor_center->z;
		//}
		else if (cnt == 6) {
			fl->x = floor_center->x + floor_size;
			fl->z = floor_center->z;
		}
		else if (cnt == 7) {
			fl->x = floor_center->x - floor_size;
			fl->z = floor_center->z - floor_size;
		}
		else if (cnt == 8) {
			fl->x = floor_center->x;
			fl->z = floor_center->z - floor_size;
		}
		else if (cnt == 9) {
			fl->x = floor_center->x + floor_size;
			fl->z = floor_center->z - floor_size;
		}
		
		++cnt;
		
		if (fl->next != NULL)
			fl = fl->next;
		else
			break;
	}
}

