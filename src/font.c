#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <GL/gl.h>

#include "nexus.h"

static GLubyte *font_data;
static GLubyte *letter_data;
static unsigned int bytes_per_line = 4*760;

static void FontMakeLetter(unsigned char letter) {
	unsigned int cnt, iter, offset;
	for (cnt = 0, offset = (letter-32)*8*4; cnt < 4*8*16; cnt += 8*4) {
		for (iter = 0; iter < 32; iter++)
			*(letter_data + cnt + iter) = *(font_data + offset + iter);
		offset += bytes_per_line;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Linear = smooth
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Nearest = crisp
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 8, 16,
				  0, GL_RGBA, GL_UNSIGNED_BYTE, letter_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontInit(void) {
	if (verbose) printf("Initializing text font\n");
	
	font_data = ImageFromPNGFile(760, 16, "images/font-760x16a.png");
	letter_data = malloc(4*8*16);

	unsigned char c;
	unsigned int cnt;
	for (cnt = 0, c = ' '; cnt <= 94; cnt++,c++)
		FontMakeLetter(c);
	
	free(font_data);
	free(letter_data);
}

void FontRender(int bgcolor, GLfloat x, GLfloat y, GLfloat z, char *text) {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	
	if (bgcolor) {
		glPushMatrix();
		glTranslatef(x, y, z);
		if (bgcolor == BG_BLACK)
			glColor4f(0.0, 0.0, 0.0, 1.0);
		else if (bgcolor == BG_GREY)
			glColor4f(0.3, 0.3, 0.3, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, -0.01);
		glVertex3f(0.0, 0.2, -0.01);
		glVertex3f(0.08*strlen(text), 0.2, -0.01);
		glVertex3f(0.08*strlen(text), 0.0, -0.01);
		glEnd();
		glPopMatrix();
	}
	
	char *c = text;
	unsigned int cnt;
	glColor3f(0.7, 0.8, 0.9);
	for (cnt = 0; cnt < strlen(text); cnt++,c++) {
		glPushMatrix();
		glTranslatef(x + cnt*0.08, y, z);
		glBindTexture(GL_TEXTURE_2D, (*c)-31);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);
		 glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0, 1.0);
		 glVertex3f(0.08, 0.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		 glVertex3f(0.08, 0.16, 0.0);
		glTexCoord2f(0.0, 0.0);
		 glVertex3f(0.0, 0.16, 0.0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
}

void FontRender2D(int bgcolor, int x, int y, char *text) {
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	
	if (bgcolor) {
		glPushMatrix();
		glTranslatef(x, y, 0.5);
		if (bgcolor == BG_BLACK)
			glColor4f(0.0, 0.0, 0.0, 1.0);
		else if (bgcolor == BG_GREY)
			glColor4f(0.3, 0.3, 0.3, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 20.0, 0.0);
		glVertex3f(8.0*strlen(text), 20.0, 0.0);
		glVertex3f(8.0*strlen(text), 0.0, 0.0);
		glEnd();
		glPopMatrix();
	}
	char *c = text;
	unsigned int cnt;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	for (cnt = 0; cnt < strlen(text); cnt++,c++) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, (*c)-31);
		//glRasterPos2i(x + cnt*9, y);
		glTranslatef((GLfloat)(x + cnt*8), (GLfloat)y, 1.0);
		glBegin(GL_POLYGON);
		glTexCoord2i(0.0, 1.0);
		 glVertex2i(0, 0);
		glTexCoord2i(1.0, 1.0);
		 glVertex2i(8, 0);
		glTexCoord2i(1.0, 0.0);
		 glVertex2i(8, 16);
		glTexCoord2i(0.0, 0.0);
		 glVertex2i(0, 16);
		glEnd();
		glPopMatrix();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

