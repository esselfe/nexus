#ifndef FLOOR_H
#define FLOOR_H 1

#include <GL/gl.h>

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

#endif /* FLOOR_H */