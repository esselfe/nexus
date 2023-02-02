#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <GL/gl.h>

GLubyte *ImageFromRawFile_128(char *filename) {
	struct stat st;
	if (stat(filename, &st) < 0) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*128*128);
		return data;
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*128*128);
		return data;
	}

	GLubyte *data = malloc(3*128*128);
	fread(data, 1, 3*128*128, fp);
	fclose(fp);

	return data;
}

GLubyte *ImageFromRawFile_884x16(char *filename) {
	struct stat st;
	if (stat(filename, &st) < 0) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*884*16);
		return data;
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*884*16);
		return data;
	}

	GLubyte *data = malloc(3*884*16);
	fread(data, 1, 3*884*16, fp);
	fclose(fp);

	return data;
}

GLubyte *ImageFromRawFile_1024(char *filename) {
	struct stat st;
	if (stat(filename, &st) < 0) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*1024*1024);
		return data;
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("nexus:%s:%s error: Cannot open %s: %s\n", __FILE__, __FUNCTION__,
			filename, strerror(errno));
		GLubyte *data = malloc(3*1024*1024);
		return data;
	}

	GLubyte *data = malloc(3*1024*1024);
	fread(data, 1, 3*1024*1024, fp);
	fclose(fp);

	return data;
}

