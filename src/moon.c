#include <stdlib.h>
#include <GL/gl.h>

#include "nexus.h"
#include "camera.h"
#include "delta.h"
#include "image.h"

static GLfloat moon_angle = 285.0;
static GLuint moon_texture_id;

void MoonInit(void) {
	GLubyte *data = ImageFromPNGFile(128, 128, "images/moon01-128ga.png");
	glGenTextures(1, &moon_texture_id);
	glBindTexture(GL_TEXTURE_2D, moon_texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void MoonMove(void) {
	moon_angle += 0.01 * delta_move;
	if (moon_angle >= 360.0)
		moon_angle -= 360.0;
}

void MoonRender(void) {
	MoonMove();
	
	glPushMatrix();
	glTranslatef(cam.x, 0.0, cam.z);
	glRotatef(moon_angle, 0.0, -1.0, 0.0);
	glTranslatef(0.0, 120.0, -900.0);
	glBindTexture(GL_TEXTURE_2D, moon_texture_id);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-10.0, -10.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-10.0, 10.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(10.0, 10.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(10.0, -10.0, 0.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

