#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <GL/gl.h>

GLubyte *ImageFromFile_128(char *filename) {
	struct stat st;
	if (stat(filename, &st) < 0) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		GLubyte *data = malloc(128*128*3);
		return data;
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		GLubyte *data = malloc(128*128*3);
		return data;
	}

	GLubyte *data = malloc(3*128*128);
	fread(data, 1, 3*128*128, fp);

	return data;
}

