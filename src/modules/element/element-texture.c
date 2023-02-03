#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>

#include "nexus.h"

GLuint texture_waste, texture_iron, texture_wood,
	texture_magnet, texture_rock;

void ElementTextureCreate(GLuint *id, char *filename) {
	GLubyte *data;

	if (strcmp(filename, "images/element-waste-128.png") == 0) {
		data = malloc(128*128*3);
		int cnt;
		for (cnt = 0; cnt < 128*128*3; cnt++)
			data[cnt] = rand()%256;
	}
	else
		data = ImageFromPNGFile_128(filename);

	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
}

void ElementTextureInit(void) {
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	ElementTextureCreate(&texture_waste, "images/element-waste-128.png");
	ElementTextureCreate(&texture_iron, "images/element-iron-128.png");
	ElementTextureCreate(&texture_wood, "images/element-wood-128.png");
	ElementTextureCreate(&texture_magnet, "images/element-magnet-128.png");
	ElementTextureCreate(&texture_rock, "images/element-rock-128.png");
}

