#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <GL/gl.h>
#include <setjmp.h>
#include <png.h>

GLubyte *ImageFromPNGFile_128(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		return NULL;
	}
	
	unsigned char sig[8];
	fread(sig, 1, 8, fp);
	if (!png_check_sig(sig, 8)) {
		printf("nexus error: PNG signature check failed: %s\n", filename);
		return NULL;
	}
	
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, NULL);
		return NULL;
	}
	png_set_sig_bytes(png, 8);
	png_init_io(png, fp);
	png_read_png(png, info, 0, 0);
	
	unsigned int components = 0, color_type = png_get_color_type(png, info);
	switch(color_type) {
	case PNG_COLOR_TYPE_GRAY:
		printf("nexus error: PNG color type gray is not supported yet\n");
		return NULL;
	case PNG_COLOR_TYPE_PALETTE:
		printf("nexus error: PNG color type palette/indexed is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_RGB:
		components = 3;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		printf("nexus error: PNG color type RGB alpha is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		printf("nexus error: PNG color type gray alpha is not supported yet\n");
		return NULL;
		break;
	default:
		printf("nexus error: Unknown png color type: %u\n", color_type);
		return NULL;
		break;
	}
	
	GLubyte *buf = malloc(128*128*3);
	png_bytepp rows = png_get_rows(png, info);
	png_bytep row;
	int x, y, cnt = 0;
	for (y = 0; y < 128; y++) {
		row = rows[y];
		for (x=0; x < 128*3; x += 3, cnt += 3) {
			buf[cnt] = row[x];
			buf[cnt+1] = row[x+1];
			buf[cnt+2] = row[x+2];
		}
	}
	
	png_destroy_read_struct(&png, &info, NULL);
	fclose(fp);
	
	return buf;
}

GLubyte *ImageFromPNGFile_760x16(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		return NULL;
	}
	
	unsigned char sig[8];
	fread(sig, 1, 8, fp);
	if (!png_check_sig(sig, 8)) {
		printf("nexus error: PNG signature check failed: %s\n", filename);
		return NULL;
	}
	
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, NULL);
		return NULL;
	}
	png_set_sig_bytes(png, 8);
	png_init_io(png, fp);
	png_read_png(png, info, 0, 0);
	
	unsigned int components = 0, color_type = png_get_color_type(png, info);
	switch(color_type) {
	case PNG_COLOR_TYPE_GRAY:
		printf("nexus error: PNG color type gray is not supported yet\n");
		return NULL;
	case PNG_COLOR_TYPE_PALETTE:
		printf("nexus error: PNG color type palette/indexed is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_RGB:
		components = 3;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		printf("nexus error: PNG color type RGB alpha is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		printf("nexus error: PNG color type gray alpha is not supported yet\n");
		return NULL;
		break;
	default:
		printf("nexus error: Unknown png color type: %u\n", color_type);
		return NULL;
		break;
	}
	
	GLubyte *buf = malloc(760*16*3);
	png_bytepp rows = png_get_rows(png, info);
	png_bytep row;
	int x, y, cnt = 0;
	for (y = 0; y < 16; y++) {
		row = rows[y];
		for (x=0; x < 760*3; x += 3, cnt += 3) {
			buf[cnt] = row[x];
			buf[cnt+1] = row[x+1];
			buf[cnt+2] = row[x+2];
		}
	}
	
	png_destroy_read_struct(&png, &info, NULL);
	fclose(fp);
	
	return buf;
}

GLubyte *ImageFromPNGFile_1024(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		return NULL;
	}
	
	unsigned char sig[8];
	fread(sig, 1, 8, fp);
	if (!png_check_sig(sig, 8)) {
		printf("nexus error: PNG signature check failed: %s\n", filename);
		return NULL;
	}
	
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, NULL);
		return NULL;
	}
	png_set_sig_bytes(png, 8);
	png_init_io(png, fp);
	png_read_png(png, info, 0, 0);
	
	unsigned int components = 0, color_type = png_get_color_type(png, info);
	switch(color_type) {
	case PNG_COLOR_TYPE_GRAY:
		printf("nexus error: PNG color type gray is not supported yet\n");
		return NULL;
	case PNG_COLOR_TYPE_PALETTE:
		printf("nexus error: PNG color type palette/indexed is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_RGB:
		components = 3;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		printf("nexus error: PNG color type RGB alpha is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		printf("nexus error: PNG color type gray alpha is not supported yet\n");
		return NULL;
		break;
	default:
		printf("nexus error: Unknown png color type: %u\n", color_type);
		return NULL;
		break;
	}
	
	GLubyte *buf = malloc(1024*1024*3);
	png_bytepp rows = png_get_rows(png, info);
	png_bytep row;
	int x, y, cnt = 0;
	for (y = 0; y < 1024; y++) {
		row = rows[y];
		for (x=0; x < 1024*3; x += 3, cnt += 3) {
			buf[cnt] = row[x];
			buf[cnt+1] = row[x+1];
			buf[cnt+2] = row[x+2];
		}
	}
	
	png_destroy_read_struct(&png, &info, NULL);
	fclose(fp);
	
	return buf;
}

GLubyte *ImageFromPNGFile_2048(char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("nexus error: Cannot open %s: %s\n", filename, strerror(errno));
		return NULL;
	}
	
	unsigned char sig[8];
	fread(sig, 1, 8, fp);
	if (!png_check_sig(sig, 8)) {
		printf("nexus error: PNG signature check failed: %s\n", filename);
		return NULL;
	}
	
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, NULL);
		return NULL;
	}
	png_set_sig_bytes(png, 8);
	png_init_io(png, fp);
	png_read_png(png, info, 0, 0);
	
	unsigned int components = 0, color_type = png_get_color_type(png, info);
	switch(color_type) {
	case PNG_COLOR_TYPE_GRAY:
		printf("nexus error: PNG color type gray is not supported yet\n");
		return NULL;
	case PNG_COLOR_TYPE_PALETTE:
		printf("nexus error: PNG color type palette/indexed is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_RGB:
		components = 3;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		printf("nexus error: PNG color type RGB alpha is not supported yet\n");
		return NULL;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		printf("nexus error: PNG color type gray alpha is not supported yet\n");
		return NULL;
		break;
	default:
		printf("nexus error: Unknown png color type: %u\n", color_type);
		return NULL;
		break;
	}
	
	GLubyte *buf = malloc(2048*2048*3);
	png_bytepp rows = png_get_rows(png, info);
	png_bytep row;
	int x, y, cnt = 0;
	for (y = 0; y < 2048; y++) {
		row = rows[y];
		for (x=0; x < 2048*3; x += 3, cnt += 3) {
			buf[cnt] = row[x];
			buf[cnt+1] = row[x+1];
			buf[cnt+2] = row[x+2];
		}
	}
	
	png_destroy_read_struct(&png, &info, NULL);
	fclose(fp);
	
	return buf;
}

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

