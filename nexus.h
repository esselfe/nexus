#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

extern char *nexus_version_string;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern GLfloat flagX, flagY, flagZ;
extern GLfloat delta;
extern unsigned int fps;
extern char *fps_text;

struct Camera {
	GLfloat x, y, z,
		lx, ly, lz;
};
extern struct Camera cam;

struct Flag {
	GLfloat x, y, z;
	unsigned int width, height, components;
	unsigned long value;
	GLuint texture_id;
	unsigned int texture_data_size;
	GLubyte *texture_data;
};
extern struct Flag flag01, flag02;

void EventCheck(void);

void FlagInit(void);
void FlagRender(void);
void FlagUpdate(void);

void FontInit(void);
void FontRender(GLfloat x, GLfloat y, GLfloat z, char *text);
void FontRender2D(int x, int y, char *text);

GLubyte *ImageFromFile_128(char *filename);
GLubyte *ImageFromFile_884x16(char *filename);

void Render(void);

#endif /* NEXUS_H */
