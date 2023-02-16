#include <stdlib.h>
#include <GL/gl.h>

#include "nexus.h"

int floor_factor;
GLfloat floor_size;
GLuint floor_texture_id;
GLfloat floor_mat_amb_diff[4];

void FloorTextureSetup(GLuint *id, unsigned int width, unsigned int height,
	  char *filename) {
	GLubyte *data = ImageFromPNGFile(width, height, filename);
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
	
	floor_size = 50.0 * floor_factor;
	
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	FloorTextureSetup(&floor_texture_id, 640, 640, "images/floor01-640.png");
}

void FloorRender(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_COLOR_MATERIAL);
	floor_mat_amb_diff[0] = daylight_amount;
	floor_mat_amb_diff[1] = daylight_amount;
	floor_mat_amb_diff[2] = daylight_amount;
	floor_mat_amb_diff[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            floor_mat_amb_diff);
	
	glBindTexture(GL_TEXTURE_2D, floor_texture_id);
	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.1, 0.1, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-floor_size, 0.0, floor_size);
	glTexCoord2f(0.0, 10.0*floor_factor);
	glVertex3f(floor_size, 0.0, floor_size);
	glTexCoord2f(10.0*floor_factor, 10.0*floor_factor);
	glVertex3f(floor_size, 0.0, -floor_size);
	glTexCoord2f(10.0*floor_factor, 0.0);
	glVertex3f(-floor_size, 0.0, -floor_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-floor_size, 0.0, floor_size);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor4f(0.15, 0.15, 0.15, 0.4);
	GLfloat cnt;
	for (cnt = -floor_size; cnt <= floor_size; cnt += 1.0) {
		glVertex3f(cnt, 0.02, floor_size);
		glVertex3f(cnt, 0.02, -floor_size);
	}
	for (cnt = floor_size; cnt >= -floor_size; cnt -= 1.0) {
		glVertex3f(-floor_size, 0.02, cnt);
		glVertex3f(floor_size, 0.02, cnt);
	}
	glEnd();
	
	floor_mat_amb_diff[0] = 0.8;
	floor_mat_amb_diff[1] = 0.8;
	floor_mat_amb_diff[2] = 0.8;
	floor_mat_amb_diff[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            floor_mat_amb_diff);
	glDisable(GL_COLOR_MATERIAL);
}

