#ifndef CAMERA_H
#define CAMERA_H 1

#include <GL/gl.h>

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

// camera.c
////////////////////////////////
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
void CameraReverse(void);
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

#endif /* CAMERA_H */