#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4,
	sky_list_1, sky_list_2, sky_list_3, sky_list_4;

void SkySetup(GLuint *id, char *filename) {
	GLubyte *data = ImageFromPNGFile(2048, 2048, filename);
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 2048, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void SkyInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	//SkySetup(&sky_texture_1, "images/sky10-2048.png");
	SkySetup(&sky_texture_1, "images/sky05-2048.png");
	SkySetup(&sky_texture_2, "images/sky06-2048.png");
	SkySetup(&sky_texture_3, "images/sky07-2048.png");
	SkySetup(&sky_texture_4, "images/sky08-2048.png");

	//////////////////////////////////
	// Generate display lists
	//////////////////////////////////

	sky_list_1 = glGenLists(1);
	glNewList(sky_list_1, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_1);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-1000.0, -1000.0, -1000.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-1000.0, 1000.0, -1000.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(1000.0, 1000.0, -1000.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(1000.0, -1000.0, -1000.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_2 = glGenLists(1);
	glNewList(sky_list_2, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(1000.0, -1000.0, -1000.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(1000.0, 1000.0, -1000.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(1000.0, 1000.0, 1000.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(1000.0, -1000.0, 1000.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_3 = glGenLists(1);
	glNewList(sky_list_3, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_3);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(1000.0, -1000.0, 1000.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(1000.0, 1000.0, 1000.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-1000.0, 1000.0, 1000.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-1000.0, -1000.0, 1000.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_4 = glGenLists(1);
	glNewList(sky_list_4, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_4);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-1000.0, -1000.0, 1000.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-1000.0, 1000.0, 1000.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-1000.0, 1000.0, -1000.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-1000.0, -1000.0, -1000.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();
}

void SkyRender(void) {
	glPushMatrix();
	glTranslatef(cam.x, cam.y, cam.z);
	glCallList(sky_list_1);
	glCallList(sky_list_2);
	glCallList(sky_list_3);
	glCallList(sky_list_4);
	glPopMatrix();
}

