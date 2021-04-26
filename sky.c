#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4,
	sky_list_1, sky_list_2, sky_list_3, sky_list_4;

void SkyInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	////////////////////////////////
	// Generate texture IDs
	////////////////////////////////

	GLubyte *data = ImageFromFile_1024("images/sky01-1024.raw");
	glGenTextures(1, &sky_texture_1);
	glBindTexture(GL_TEXTURE_2D, sky_texture_1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
	free(data);

	data = ImageFromFile_1024("images/sky02-1024.raw");
	glGenTextures(1, &sky_texture_2);
	glBindTexture(GL_TEXTURE_2D, sky_texture_2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
	free(data);

	data = ImageFromFile_1024("images/sky03-1024.raw");
	glGenTextures(1, &sky_texture_3);
	glBindTexture(GL_TEXTURE_2D, sky_texture_3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
	free(data);

	data = ImageFromFile_1024("images/sky04-1024.raw");
	glGenTextures(1, &sky_texture_4);
	glBindTexture(GL_TEXTURE_2D, sky_texture_4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
	free(data);

	//////////////////////////////////
	// Generate display lists
	//////////////////////////////////

	sky_list_1 = glGenLists(1);
	glNewList(sky_list_1, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_1);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cam.x, cam.y, cam.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-100.0, -100.0, -100.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-100.0, 100.0, -100.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(100.0, 100.0, -100.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(100.0, -100.0, -100.0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_2 = glGenLists(1);
	glNewList(sky_list_2, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_2);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cam.x, cam.y, cam.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(100.0, -100.0, -100.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(100.0, 100.0, -100.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(100.0, 100.0, 100.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(100.0, -100.0, 100.0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_3 = glGenLists(1);
	glNewList(sky_list_3, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_3);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cam.x, cam.y, cam.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(100.0, -100.0, 100.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(100.0, 100.0, 100.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-100.0, 100.0, 100.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-100.0, -100.0, 100.0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	sky_list_4 = glGenLists(1);
	glNewList(sky_list_4, GL_COMPILE_AND_EXECUTE);
	glBindTexture(GL_TEXTURE_2D, sky_texture_4);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cam.x, cam.y, cam.z);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-100.0, -100.0, 100.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-100.0, 100.0, 100.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-100.0, 100.0, -100.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-100.0, -100.0, -100.0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();
}

void SkyRender(void) {
	glCallList(sky_list_1);
	glCallList(sky_list_2);
	glCallList(sky_list_3);
	glCallList(sky_list_4);
}

