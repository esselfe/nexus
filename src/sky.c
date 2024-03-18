#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"
#include "camera.h"
#include "delta.h"
#include "image.h"
#include "moon.h"
#include "render.h"
#include "sky.h"

GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4,
	sky_list, daylight_list;
GLfloat daylight_amount;
char daylight_amount_text[10];
int daylight_enabled = 1;
int daylight_up;
GLfloat dlcnt; // Used to "pause" on day or night state for a little while

void SkySetup(GLuint *id, char *filename) {
	if (verbose) printf("  Loading sky texture from %s\n", filename);
	GLubyte *data = ImageFromPNGFile(2048, 2048, filename);
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void SkyInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	
	daylight_up = 1;
	daylight_amount = 0.5;
	sprintf(daylight_amount_text, "%.1f", daylight_amount);
	
	if (verbose) printf("Generating sky textures\n");
	
	SkySetup(&sky_texture_1, "images/sky01-2048.png");
	SkySetup(&sky_texture_2, "images/sky02-2048.png");
	SkySetup(&sky_texture_3, "images/sky03-2048.png");
	SkySetup(&sky_texture_4, "images/sky04-2048.png");

	//////////////////////////////////
	// Generate display lists
	//////////////////////////////////

	sky_list = glGenLists(1);
	glNewList(sky_list, GL_COMPILE);
	
	// North side
	glBindTexture(GL_TEXTURE_2D, sky_texture_1);
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
	
	// East side
	glBindTexture(GL_TEXTURE_2D, sky_texture_2);
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
	
	// South side
	glBindTexture(GL_TEXTURE_2D, sky_texture_3);
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
	
	// West side
	glBindTexture(GL_TEXTURE_2D, sky_texture_4);
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
	glNewList(daylight_list, GL_COMPILE);
	
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

void SkyRender(void) {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_BLEND);
	
	glPushMatrix();
	glTranslatef(cam.x, cam.y, -cam.z);
	if (daylight_enabled)
		glColor3f(1.4-daylight_amount, 1.4-daylight_amount, 1.4-daylight_amount);
	else
		glColor3f(1.0, 1.0, 1.0);
	glCallList(sky_list);
	
	if (daylight_enabled) {
		glEnable(GL_BLEND);
		glColor4f(0.6*daylight_amount, 0.6*daylight_amount, 0.8, daylight_amount);
		glCallList(daylight_list);
	}
	glPopMatrix();
	
	MoonRender();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	if (daylight_enabled) {
		if (daylight_up && daylight_amount < 1.0) {
			daylight_amount += 0.0001 * delta_move;
			sprintf(daylight_amount_text, "%.3f", daylight_amount);
			light_ambient[0] = daylight_amount;
			light_ambient[1] = daylight_amount;
			light_ambient[2] = daylight_amount;
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		}
		else if (!daylight_up && daylight_amount > 0.0) {
			daylight_amount -= 0.0001 * delta_move;
			sprintf(daylight_amount_text, "%.3f", daylight_amount);
			light_ambient[0] = daylight_amount;
			light_ambient[1] = daylight_amount;
			light_ambient[2] = daylight_amount;
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		}
		
		if (daylight_up && daylight_amount >= 1.0)
			dlcnt += delta_move;
		else if (!daylight_up && daylight_amount <= 0.0)
			dlcnt -= delta_move;
		
		if (daylight_up && daylight_amount >= 1.0 && dlcnt >= 1000)
			daylight_up = 0;
		else if (!daylight_up && daylight_amount <= 0.0 && dlcnt <= 0)
			daylight_up = 1;
	}
}

