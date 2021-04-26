#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <GL/gl.h>

#include "nexus.h"

static GLubyte *font_data;
static GLubyte *letter_data;
static unsigned int bytes_per_line = 3*884;

static void FontMakeLetter(unsigned char letter) {
    unsigned int cnt, iter, offset;
    for (cnt = 0, offset = (letter-30)*9*3-15; cnt < 3*8*16; cnt += 8*3) {
        for (iter = 0; iter < 24; iter++)
            *(letter_data + cnt + iter) = *(font_data + offset + iter);
        offset += bytes_per_line;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 8, 16,
                  0, GL_RGB, GL_UNSIGNED_BYTE, letter_data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FontInit(void) {
	font_data = ImageFromFile_884x16("images/font-884x16.raw");
	letter_data = malloc(3*8*16);

	unsigned char c;
	unsigned int cnt;
    for (cnt = 0, c = ' '; cnt < 94; cnt++,c++)
        FontMakeLetter(c);
	
    free(font_data);
    free(letter_data);
}

void FontRender(GLfloat x, GLfloat y, GLfloat z, char *text) {
	char *c = text;
	unsigned int cnt;
	glColor3f(0.7, 0.8, 0.9);
    for (cnt = 0; cnt < strlen(text); cnt++,c++) {
        glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, (*c)-31);
		glTranslatef(cnt*0.08, 1.2, 0.0);
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
		glPopMatrix();
	}
}

void FontRender2D(int x, int y, char *text) {
	char *c = text;
	unsigned int cnt;
	glColor3f(0.7, 0.8, 0.9);
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

