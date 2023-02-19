#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "nexus.h"

struct Flag flag01, flag02;
static GLfloat flag_mat_amb_diff[4];

void FlagSetup(struct Flag *flag, char *filename) {
	flag->width = 128;
	flag->height = 128;
	flag->components = 3;
	flag->value = (rand()%10000) + 1;
	flag->texture_data_size = flag->width * flag->height * flag->components;
	if (filename == NULL) {
		flag->texture_data = malloc(flag->texture_data_size);
		unsigned int cnt;
		for (cnt = 0; cnt < flag->texture_data_size; cnt++)
			flag->texture_data[cnt] = rand()%256;
	}
	else
		flag->texture_data = ImageFromPNGFile(128, 128, filename);
	glGenTextures(1, &flag->texture_id);
	glBindTexture(GL_TEXTURE_2D, flag->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, flag->texture_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FlagInit(void) {
	if (verbose) printf("Initializing flags\n");
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	flag01.x = -5.0;
	flag01.y = 0.5;
	flag01.z = 0.0;
	FlagSetup(&flag01, "images/flag01-128.png");

	flag02.x = 5.0;
	flag02.y = 0.5;
	flag02.z = 0.0;
	FlagSetup(&flag02, NULL);
}

void FlagRender(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_BLEND);
	flag_mat_amb_diff[0] = daylight_amount;
	flag_mat_amb_diff[1] = daylight_amount;
	flag_mat_amb_diff[2] = daylight_amount;
	flag_mat_amb_diff[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
            flag_mat_amb_diff);
	
	glBindTexture(GL_TEXTURE_2D, flag01.texture_id);
	glPushMatrix();
	glTranslatef(flag01.x, flag01.y, flag01.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, flag02.texture_id);
	glPushMatrix();
	glTranslatef(flag02.x, flag02.y, flag02.z);
	glRotatef(delta, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void FlagUpdate(void) {
	flag01.x += (GLfloat)((rand()%3)+1)/100.0 - (GLfloat)(rand()%6)/100.0;
	flag01.z += (GLfloat)((rand()%3)+1)/100.0 - (GLfloat)(rand()%6)/100.0;

	flag02.z += (GLfloat)(rand()%3)/100.0;
	if (flag02.z >= 50.0 * floor_factor)
		flag02.z -= 50.0 * floor_factor * 2;
}

