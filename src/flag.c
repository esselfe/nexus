#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "nexus.h"

struct Flag flag01, flag02;

void FlagInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	flag01.x = -5.0;
	flag01.y = 0.5;
	flag01.z = 0.0;
	flag01.width = 128;
	flag01.height = 128;
	flag01.components = 3;
	flag01.value = (rand()%10000) + 1;
	flag01.texture_data_size = flag01.width * flag01.height * flag01.components;
	flag01.texture_data = ImageFromFile_128("images/flag01-128.raw");
	glGenTextures(1, &flag01.texture_id);
	glBindTexture(GL_TEXTURE_2D, flag01.texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, flag01.texture_data);
	glBindTexture(GL_TEXTURE_2D, 0);

	flag02.x = 5.0;
	flag02.y = 0.5;
	flag02.z = 0.0;
	flag02.width = 128;
	flag02.height = 128;
	flag02.components = 3;
	flag02.value = (rand()%10000) + 1;
	flag02.texture_data_size = flag02.width * flag02.height * flag02.components;
	flag02.texture_data = malloc(flag02.texture_data_size);
	unsigned int cnt;
	for (cnt = 0; cnt < flag02.texture_data_size; cnt++)
		flag02.texture_data[cnt] = rand()%256;
	glGenTextures(1, &flag02.texture_id);
	glBindTexture(GL_TEXTURE_2D, flag02.texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, flag02.texture_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FlagRender(void) {
	glBindTexture(GL_TEXTURE_2D, flag01.texture_id);
	glPushMatrix();
	glTranslatef(flag01.x, flag01.y, flag01.z);
	glColor3f(0.6, 0.7, 0.8);
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
	glColor3f(0.6, 0.7, 0.8);
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
	if (flag02.z >= 100.0)
		flag02.z -= 200.0;
}

