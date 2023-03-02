#include <stdlib.h>
#include <GL/gl.h>

#include "nexus.h"

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
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
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
	fl->offset_z = -1;
	fl->x = -floor_size;
	fl->y = 0.0;
	fl->z = -floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// north
	fl->offset_x = 0;
	fl->offset_z = -1;
	fl->x = 0.0;
	fl->y = 0.0;
	fl->z = -floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// northeast
	fl->offset_x = 1;
	fl->offset_z = -1;
	fl->x = floor_size;
	fl->y = 0.0;
	fl->z = -floor_size;
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
	fl->offset_z = 1;
	fl->x = -floor_size;
	fl->y = 0.0;
	fl->z = floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// south
	fl->offset_x = 0;
	fl->offset_z = 1;
	fl->x = 0.0;
	fl->y = 0.0;
	fl->z = floor_size;
	fl->texture_id = floor_texture_id;
	fl->next = malloc(sizeof(struct Floor));
	fl->next->prev = fl;
	fl = fl->next;
	
	// southeast
	fl->offset_x = 1;
	fl->offset_z = 1;
	fl->x = floor_size;
	fl->y = 0.0;
	fl->z = floor_size;
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
		glTranslatef(fl->x, fl->y, fl->z);
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
		glPopMatrix();
		
		if (fl->next != NULL)
			fl = fl->next;
		else
			break;
	}
}

void FloorAddNorthRow(void) {
	return;
}

void FloorAddSouthRow(void) {
	return;
}

void FloorAddWestRow(void) {
	return;
}

void FloorAddEastRow(void) {
	return;
}

