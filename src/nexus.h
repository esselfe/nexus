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
#define MOVE_BREAK        (1<<16)
#define MOVE_SIDE_BREAK   (1<<17)
struct Camera {
	GLfloat x, y, z, // position
		lx, ly, lz; // look_at point position
	GLfloat rotation_angle; // Y axis rotation
	unsigned long moving; // Each bit is a movement flag from above
	GLfloat thr, // Throttle
		speed, side_speed, height_speed;
	char thr_text[5], speed_text[5], side_speed_text[5],
		height_speed_text[5]; // 2D HUD text
};
extern struct Camera cam; // For now there's only one... a list would be nice.

void CameraInit(void);
void CameraMove(void);
void CameraReset(void);
void CameraRotateStep(GLfloat angle);
void CameraShowPosition(void);
void CameraStop(void);

// camera-goto.c
////////////////////////////////
extern int goto_enabled, goto_stopping; // Automation flags
extern GLfloat goto_x, goto_z;
// Gradually changes camera position
void CameraGoto(GLfloat x, GLfloat z);
void CameraGotoMove(void);

// camera-jump.c
////////////////////////////////
// Immediately changes camera position
void CameraJump(GLfloat x, GLfloat z);

// delta.c
////////////////////////////////
extern GLfloat delta, delta_move;
void DeltaCompute(void);
void DeltaInit(void);
extern void (*DeltaFunc)(void); // Modules are supposed to associate this handler to their function
void DeltaMove(void);

// event.c
////////////////////////////////
#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_ALT     (1<<1)
#define MOD_SHIFT   (1<<2)
extern unsigned int mods; // Each bit can be set to one of the flags above
extern unsigned int show_keys; // Show keys pressed on the standard output stream
extern int mouse_x, mouse_y, mouse_x_prev, mouse_y_prev;
extern unsigned int mouse_held; // Mouse moves camera rotation or cursor

void EventCheck(void);
extern void (*EventFunc)(void); // Modules are supposed to associate this handler to their function
void EventInit(void);

// flag.c
////////////////////////////////
struct Flag {
	GLfloat x, y, z;
	unsigned int width, height;
	unsigned long value;
	GLuint texture_id;
};
extern struct Flag flag01, flag02;

void FlagInit(void);
void FlagRender(void);
void FlagUpdate(void);

// floor.c
////////////////////////////////
// 9 floors total, popping and pushing floors when camera crosses center's borders
struct Floor {
	struct Floor *prev, *next;
	int offset_x, offset_z;
	GLfloat size, x, y, z;
	GLuint texture_id;
};
struct FloorList {
	struct Floor *first_floor, *last_floor;
};
extern struct FloorList floor_root_list;
extern struct Floor *floor_center; // Points to the 5th floor in the list
extern int floor_freeze; // To stop generating/removing floors
// A default floor size is multiplicated by this
// It can be set with one of the program's options on the command line
extern int floor_factor;
extern GLfloat floor_size;
extern GLuint floor_texture_id; // There's only one for now
void FloorInit(void);
void FloorAddNorthRow(void);
void FloorAddSouthRow(void);
void FloorAddWestRow(void);
void FloorAddEastRow(void);
void FloorRender(void);
void FloorResetSize(void);

// font.c
////////////////////////////////
// Text background and foreground colors
#define BG_NONE    0
#define BG_BLACK   1
#define BG_GRAY    2
#define BG_GREY    2
#define FG_NONE    0
#define FG_BLUE    1
#define FG_GREEN   2
void FontInit(void);
// 3D-positioned scene text
void FontRender(int bgcolor, int fgcolor, GLfloat x, GLfloat y, GLfloat z, char *text);
// HUD text
void FontRender2D(int bgcolor, int x, int y, char *text);

// image.c
////////////////////////////////
// Used to create textures
GLubyte *ImageFromPNGFile(unsigned int width, unsigned int height, char *filename);

// mode.c
////////////////////////////////
#define MODE_MAIN      0
#define MODE_BROWSER   1
#define MODE_DRIVING   2
#define MODE_EDITOR    3
#define MODE_ELEMENT   4
#define MODE_MEMORY    5
extern unsigned int mode, mode_prev;
unsigned int ModeGet(void);
void ModeSet(unsigned int newmode);

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
extern int render; // Used for ignoring some calls when picking
void Render(void);
void RenderCompass(void);
void RenderCursor(void);
extern void (*RenderFunc)(void); // Modules are supposed to associate this handler to their function
void RenderInit(void);
void RenderSet2DView(void);
void RenderSet3DView(void);
void RenderThrottle(void); // Draw the throttle meter on the HUD

// sky.c
////////////////////////////////
// The sky is a box without bottom or top, only 4 of 6 sides
extern GLuint sky_texture_1, sky_texture_2, sky_texture_3, sky_texture_4;
extern GLfloat daylight_amount;
extern char daylight_amount_text[10];
extern int daylight_enabled;
extern int daylight_up;
void SkyInit(void);
void SkyRender(void);

// terminal.c
////////////////////////////////
#define TERMINAL_BUFFER_SIZE 4096
extern unsigned int terminal_visible; // Enables or disables the terminal
extern char terminal_buffer[TERMINAL_BUFFER_SIZE];
extern unsigned int terminal_cursor_pos,
	terminal_cursor_blink; // Toggled once every half second
void TerminalParse(void);
void TerminalRender(void);

////////////////////////////////////////////////////////////////
// Modules
////////////////////////////////////////////////////////////////

// File browser
////////////////////////////////
#define ENTRY_TYPE_UNKNOWN    0
#define ENTRY_TYPE_DIRECTORY  1
#define ENTRY_TYPE_EXECUTABLE 2
#define ENTRY_TYPE_FILE       3
struct BrowserListEntry {
	struct BrowserListEntry *prev, *next;
	unsigned int type;
	unsigned int rank;
	char *name;
};
struct BrowserList {
	struct BrowserListEntry *first_entry, *last_entry;
	unsigned long entry_total;
};
extern struct BrowserList browser_list;
extern struct BrowserListEntry *browser_selected_entry;
extern GLuint browser_select_buffer[100];
void BrowserInit(void);
void BrowserListAddEntry(unsigned int type, char *name);
void BrowserListLoad(char *path);
void BrowserListDestroy(void);
struct BrowserListEntry *BrowserListEntryByRank(unsigned int rank);
void BrowserPickingCheck(void);
void BrowserRender(void);

// Driving
////////////////////////////////
void DrivingDelta(void);
void DrivingEvent(void);
void DrivingRender(void);

// Editor
////////////////////////////////
struct LineNode {
	struct LineNode *prev, *next;
	unsigned long long line_number;
	unsigned long long length;
	char *text;
};
struct LineList {
	struct LineNode *first_line, *last_line;
	unsigned long long total_lines;
};
extern struct LineList line_root_list;

void EditorInit(void);
void EditorLoadFile(char *filename);
void EditorLineAdd(char *text);
void EditorLineRemove(unsigned long long line_number);
void EditorRender(void);

// Element
////////////////////////////////
#define ELEMENT_TYPE_WASTE   0
#define ELEMENT_TYPE_BATTERY 1
#define ELEMENT_TYPE_COPPER  2
#define ELEMENT_TYPE_GOLD    3
#define ELEMENT_TYPE_IRON    4
#define ELEMENT_TYPE_MAGNET  5
#define ELEMENT_TYPE_ROCK    6
#define ELEMENT_TYPE_SILVER  7
#define ELEMENT_TYPE_WOOD    8
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
extern unsigned long long total_waste, total_battery, total_copper, total_gold,
	total_iron, total_magnet, total_rock, total_silver, total_wood;
extern GLuint texture_id_waste, texture_id_battery, texture_id_copper,
	texture_id_gold, texture_id_iron, texture_id_magnet, texture_id_rock,
	texture_id_silver, texture_id_wood;
extern GLfloat element_mat_amb_diff[4];
extern struct timeval tv_score_saved;
void ElementAdd(unsigned int count);
void ElementCleanArea(void);
void ElementDelta(void);
void ElementInit(void);
void ElementListDestroy(void);
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
extern GLfloat memory_mat_amb_diff[4];
void MemoryDeltaCompute(void);
void MemoryInit(void);
void MemoryRender(void);

#endif /* NEXUS_H */
