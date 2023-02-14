#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4,
	sky_list, daylight_list;

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

	sky_list = glGenLists(1);
	glNewList(sky_list, GL_COMPILE_AND_EXECUTE);
	
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
	
	daylight_list = glGenLists(1);
	glNewList(daylight_list, GL_COMPILE_AND_EXECUTE);
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-975.0, -975.0, -975.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-975.0, 975.0, -975.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(975.0, 975.0, -975.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(975.0, -975.0, -975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(975.0, -975.0, -975.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(975.0, 975.0, -975.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(975.0, 975.0, 975.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(975.0, -975.0, 975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(975.0, -975.0, 975.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(975.0, 975.0, 975.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-975.0, 975.0, 975.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-975.0, -975.0, 975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	 glVertex3f(-975.0, -975.0, 975.0);
	glTexCoord2f(1.0, 1.0);
	 glVertex3f(-975.0, 975.0, 975.0);
	glTexCoord2f(1.0, 0.0);
	 glVertex3f(-975.0, 975.0, -975.0);
	glTexCoord2f(0.0, 0.0);
	 glVertex3f(-975.0, -975.0, -975.0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();
}

GLfloat daylight_amount;
int daylight_up = 1;
void SkyRender(void) {
	glPushMatrix();
	glTranslatef(cam.x, cam.y, cam.z);
	glCallList(sky_list);
	glColor4f(0.6, 0.6, 0.8, daylight_amount);
	glCallList(daylight_list);
	glPopMatrix();
	
	if (daylight_up) daylight_amount += 0.0001 * delta_move;
	else daylight_amount -= 0.0001 * delta_move;
	
	if (daylight_up && daylight_amount >= 1.0)
		daylight_up = 0;
	else if (!daylight_up && daylight_amount <= 0.0)
		daylight_up = 1;
}

