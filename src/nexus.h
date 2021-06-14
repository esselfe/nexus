#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

// nexus.c
extern char *nexus_version_string;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern GLfloat delta;
extern unsigned int fps;
extern char *fps_text;

extern time_t t0, tprev;
extern struct timeval tv0, tv_prev, tv_diff;
void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2);

// camera.c
#define MOVE_NONE   0
#define MOVE_LEFT   1
#define MOVE_RIGHT  (1<<1)
#define MOVE_FRONT  (1<<2)
#define MOVE_BACK   (1<<3)
#define MOVE_UP     (1<<4)
#define MOVE_DOWN   (1<<5)
struct Camera {
	GLfloat x, y, z,
		lx, ly, lz;
	GLfloat rotation_angle;
	unsigned int moving;
	GLfloat thr;
	char thr_text[5];
};
extern struct Camera cam;

void CameraMove(void);
void CameraRotateStep(GLfloat angle);

// delta.c
void DeltaCompute(void);
extern void (*DeltaFunc)(void);

// event.c
#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_ALT     (1<<1)
#define MOD_SHIFT   (1<<2)
extern unsigned int mods;
extern unsigned int show_keys;
extern int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
extern unsigned int mouse_held;

void EventCheck(void);

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

// font.c
void FontInit(void);
void FontRender(GLfloat x, GLfloat y, GLfloat z, char *text);
void FontRender2D(int x, int y, char *text);

// image.c
GLubyte *ImageFromFile_128(char *filename);
GLubyte *ImageFromFile_884x16(char *filename);
GLubyte *ImageFromFile_1024(char *filename);

// render.c
void Render(void);
void RenderCursor(void);
void RenderFloor(void);
extern void (*RenderFunc)(void);

// sky.c
extern GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;

void SkyInit(void);
void SkyRender(void);

// state.c
#define STATE_MAIN      0
#define STATE_BROWSER   1
#define STATE_EDITOR    2
#define STATE_MEMORY    3
extern unsigned int state, state_prev;

unsigned int StateGet(void);
void StateSet(unsigned int newstate);

// terminal.c
#define TERMINAL_BUFFER_SIZE 4096
extern unsigned int terminal_visible;
extern char terminal_buffer[TERMINAL_BUFFER_SIZE];
extern unsigned int terminal_cursor_pos, terminal_cursor_blink;

void TerminalParse(void);
void TerminalRender(void);

////////////////////////////////
// Modules
////////////////////////////////

struct BrowserListEntry {
	struct BrowserListEntry *prev, *next;
	unsigned int rank;
	char *name;
};
struct BrowserList {
	struct BrowserListEntry *first_entry, *last_entry;
	unsigned long entry_total;
};
extern struct BrowserList browser_list;
void BrowserListAddEntry(char *name);
void BrowserListLoad(char *path);
void BrowserListDestroy(void);
void BrowserRender(void);

void EditorRender(void);

extern GLfloat memory_max, memory_value;
extern char memory_max_text[128], memory_value_text[128];
extern GLfloat swap_max, swap_value;
extern char swap_max_text[128], swap_value_text[128];
void MemoryDeltaCompute(void);
void MemoryRender(void);

#endif /* NEXUS_H */
