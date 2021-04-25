#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

// nexus.c
extern char *nexus_version_string;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern GLfloat flagX, flagY, flagZ;
extern GLfloat delta;
extern unsigned int fps;
extern char *fps_text;

// camera.c
struct Camera {
	GLfloat x, y, z,
		lx, ly, lz;
};
extern struct Camera cam;

// flag.c
struct Flag {
	GLfloat x, y, z;
	unsigned int width, height, components;
	unsigned long value;
	GLuint texture_id;
	unsigned int texture_data_size;
	GLubyte *texture_data;
};
extern struct Flag flag01, flag02;

void FlagInit(void);
void FlagRender(void);
void FlagUpdate(void);

// event.c
void EventCheck(void);

// font.c
void FontInit(void);
void FontRender(GLfloat x, GLfloat y, GLfloat z, char *text);
void FontRender2D(int x, int y, char *text);

// image.c
GLubyte *ImageFromFile_128(char *filename);
GLubyte *ImageFromFile_884x16(char *filename);

// render.c
void Render(void);
extern void (*RenderFunc)(void);

// state.c
#define STATE_MAIN      0
#define STATE_BROWSER   1
#define STATE_EDITOR    2
#define STATE_MEMORY    3
extern unsigned int state, state_prev;

unsigned int StateGet(void);
void StateSet(unsigned int newstate);

////////////////////////////////
// Modules
////////////////////////////////

void BrowserRender(void);

void EditorRender(void);

void MemoryRender(void);

#endif /* NEXUS_H */
