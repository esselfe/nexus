#ifndef NEXUS_H
#define NEXUS_H 1

#include <GL/gl.h>
#include <SDL2/SDL.h>

////////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////////

// nexus.c
////////////////////////////////
extern char *nexus_version_string;
extern int verbose;
extern int mainloopend;
extern SDL_Window *window;
extern GLfloat winX, winY, winW, winH;
extern unsigned int fps;
extern char *fps_text;

extern time_t t0, tprev;
extern struct timeval tv0, tv_prev, tv_diff;
void tvdiff(struct timeval *tv_start, struct timeval *tv_end, struct timeval *tv_diff2);

// camera.c
////////////////////////////////
#define MOVE_NONE         0
#define MOVE_LEFT         1
#define MOVE_RIGHT        (1<<1)
#define MOVE_FRONT        (1<<2)
#define MOVE_BACK         (1<<3)
#define MOVE_UP           (1<<4)
#define MOVE_DOWN         (1<<5)
#define LOOK_LEFT         (1<<6)
#define LOOK_RIGHT        (1<<7)
#define THR_UP            (1<<8)
#define THR_DOWN          (1<<9)
#define MOVE_ACCEL        (1<<10)
#define MOVE_DECEL        (1<<11)
#define MOVE_SIDE_ACCEL   (1<<12)
#define MOVE_SIDE_DECEL   (1<<13)
#define MOVE_HEIGHT_ACCEL (1<<14)
#define MOVE_HEIGHT_DECEL (1<<15)
struct Camera {
	GLfloat x, y, z,
		lx, ly, lz;
	GLfloat rotation_angle;
	unsigned long moving;
	GLfloat thr, speed, side_speed, height_speed;
	char thr_text[5], speed_text[5], side_speed_text[5],
		height_speed_text[5];
};
extern struct Camera cam;

void CameraInit(void);
void CameraMove(void);
void CameraRotateStep(GLfloat angle);
void CameraStop(void);

// camera-goto.c
////////////////////////////////
extern int goto_enabled;
void CameraGoto(GLfloat x, GLfloat z);
void CameraGotoMove(void);

// camera-jump.c
////////////////////////////////
void CameraJump(GLfloat x, GLfloat z);

// delta.c
////////////////////////////////
extern GLfloat delta, delta_move;
void DeltaCompute(void);
void DeltaInit(void);
extern void (*DeltaFunc)(void); // Modules are supposed to associate this handler to their funtion
void DeltaMove(void);

// event.c
////////////////////////////////
#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_ALT     (1<<1)
#define MOD_SHIFT   (1<<2)
extern unsigned int mods;
extern unsigned int show_keys;
extern int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
extern unsigned int mouse_held;

void EventCheck(void);
extern void (*EventFunc)(void); // Modules are supposed to associate this handler to their funtion
void EventInit(void);

// flag.c
////////////////////////////////
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

// floor.c
////////////////////////////////
extern int floor_factor;
void FloorInit(void);
void FloorRender(void);

// font.c
////////////////////////////////
#define BG_NONE    0
#define BG_BLACK   1
#define BG_GRAY    2
#define BG_GREY    2
void FontInit(void);
void FontRender(int bgcolor, GLfloat x, GLfloat y, GLfloat z, char *text);
void FontRender2D(int bgcolor, int x, int y, char *text);

// image.c
////////////////////////////////
GLubyte *ImageFromPNGFile(unsigned int width, unsigned int height, char *filename);

// moon.c
////////////////////////////////
void MoonInit(void);
void MoonMove(void);
void MoonRender(void);

// render.c
////////////////////////////////
extern GLfloat light_ambient[];
extern GLfloat light_diffuse[];
extern GLfloat light_specular[];
extern GLfloat light_position[];
extern int render;
void Render(void);
void RenderCompass(void);
void RenderCursor(void);
extern void (*RenderFunc)(void); // Modules are supposed to associate this handler to their funtion
void RenderInit(void);
void RenderSet2DView(void);
void RenderSet3DView(void);
void RenderThrottle(void);

// sky.c
////////////////////////////////
extern GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;
extern GLfloat daylight_amount;
extern int daylight_up;
void SkyInit(void);
void SkyRender(void);

// state.c
////////////////////////////////
#define STATE_MAIN      0
#define STATE_BROWSER   1
#define STATE_DRIVING   2
#define STATE_EDITOR    3
#define STATE_ELEMENT   4
#define STATE_MEMORY    5
extern unsigned int state, state_prev;

unsigned int StateGet(void);
void StateSet(unsigned int newstate);

// terminal.c
////////////////////////////////
#define TERMINAL_BUFFER_SIZE 4096
extern unsigned int terminal_visible;
extern char terminal_buffer[TERMINAL_BUFFER_SIZE];
extern unsigned int terminal_cursor_pos, terminal_cursor_blink;

void TerminalParse(void);
void TerminalRender(void);

////////////////////////////////////////////////////////////////
// Modules
////////////////////////////////////////////////////////////////

// Browser
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
void BrowserInit(void);
void BrowserListAddEntry(char *name);
void BrowserListLoad(char *path);
void BrowserListDestroy(void);
void BrowserRender(void);

// Driving
////////////////////////////////
void DrivingDelta(void);
void DrivingEvent(void);
void DrivingRender(void);

// Editor
////////////////////////////////
void EditorRender(void);

// Element
////////////////////////////////
#define ELEMENT_TYPE_WASTE  0
#define ELEMENT_TYPE_IRON   1
#define ELEMENT_TYPE_WOOD   2
#define ELEMENT_TYPE_MAGNET 3
#define ELEMENT_TYPE_ROCK   4
struct Element {
	struct Element *prev, *next;
	unsigned int type;
	unsigned int value;
	float x, y, z;
	float width, height;
	float angle_x, angle_y, angle_z;
	GLuint texture_id;
};
struct ElementList {
	struct Element *first_element, *last_element;
	unsigned int total_elements;
};
extern struct ElementList element_root_list;
extern unsigned long long total_waste, total_iron, total_wood,
	total_magnet, total_rock;
extern GLuint texture_id_waste, texture_id_iron, texture_id_wood,
	texture_id_magnet, texture_id_rock;
extern struct timeval tv_score_saved;
void ElementAdd(unsigned int count);
void ElementDelta(void);
void ElementListDestroy(void);
void ElementInit(void);
void ElementRemove(struct Element *elem);
void ElementRender(void);
void ElementScoreLoad(void);
void ElementScoreSave(void);
void ElementTextureInit(void);
void ElementThreadStart(void);

// Memory
////////////////////////////////
extern GLfloat memory_max, memory_value;
extern char memory_max_text[128], memory_value_text[128];
extern GLfloat swap_max, swap_value;
extern char swap_max_text[128], swap_value_text[128];
void MemoryDeltaCompute(void);
void MemoryRender(void);

#endif /* NEXUS_H */
