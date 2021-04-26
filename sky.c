#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;

void SkyInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

}

void SkyRender(void) {
	//glColor3f(0.3, 0.3, 0.3);
	glBindTexture(GL_TEXTURE_2D, sky_texture_1);
	glPushMatrix();
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

	glBindTexture(GL_TEXTURE_2D, sky_texture_2);
	glPushMatrix();
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

	glBindTexture(GL_TEXTURE_2D, sky_texture_3);
	glPushMatrix();
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

	glBindTexture(GL_TEXTURE_2D, sky_texture_4);
	glPushMatrix();
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
}

