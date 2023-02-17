#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4,
	sky_list, daylight_list;
GLfloat daylight_amount;
int daylight_up = 1;

void SkySetup(GLuint *id, char *filename) {
	printf("  Loading sky texture from %s\n", filename);
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
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	
	daylight_amount = 0.1;
	
	if (verbose) printf("Generating sky textures\n");
	
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
	 glVertex3f(-975.0, -975.0, -975.0);
	 glVertex3f(-975.0, 975.0, -975.0);
	 glVertex3f(975.0, 975.0, -975.0);
	 glVertex3f(975.0, -975.0, -975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	 glVertex3f(975.0, -975.0, -975.0);
	 glVertex3f(975.0, 975.0, -975.0);
	 glVertex3f(975.0, 975.0, 975.0);
	 glVertex3f(975.0, -975.0, 975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	 glVertex3f(975.0, -975.0, 975.0);
	 glVertex3f(975.0, 975.0, 975.0);
	 glVertex3f(-975.0, 975.0, 975.0);
	 glVertex3f(-975.0, -975.0, 975.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	 glVertex3f(-975.0, -975.0, 975.0);
	 glVertex3f(-975.0, 975.0, 975.0);
	 glVertex3f(-975.0, 975.0, -975.0);
	 glVertex3f(-975.0, -975.0, -975.0);
	glEnd();
	
	glEndList();
}

GLfloat dlcnt;
void SkyRender(void) {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	
	glPushMatrix();
	glTranslatef(cam.x, cam.y, cam.z);
	glCallList(sky_list);
	glEnable(GL_BLEND);
	glColor4f(0.6*daylight_amount, 0.6*daylight_amount, 0.8, daylight_amount);
	glCallList(daylight_list);
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	if (daylight_up && daylight_amount < 1.0) {
		daylight_amount += 0.0001 * delta_move;
		light_ambient[0] = daylight_amount;
		light_ambient[1] = daylight_amount;
		light_ambient[2] = daylight_amount;
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	else if (!daylight_up && daylight_amount > 0.2) {
		daylight_amount -= 0.0001 * delta_move;
		light_ambient[0] = daylight_amount;
		light_ambient[1] = daylight_amount;
		light_ambient[2] = daylight_amount;
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	
	if (daylight_up && daylight_amount >= 1.0)
		dlcnt += delta_move;
	else if (!daylight_up && daylight_amount <= 0.2)
		dlcnt -= delta_move;
	
	if (daylight_up && daylight_amount >= 1.0 && dlcnt >= 1000)
		daylight_up = 0;
	else if (!daylight_up && daylight_amount <= 0.2 && dlcnt <= 0)
		daylight_up = 1;
}

