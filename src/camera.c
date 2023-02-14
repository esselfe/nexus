#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include "nexus.h"

struct Camera cam;

void CameraInit(void) {
	if (verbose) printf("Initializing camera\n");
	cam.x = 0.0;
	cam.y = 2.0;
	cam.z = 10.0;
	cam.rotation_angle = 180.0;
	cam.lx = (GLfloat)sin(cam.rotation_angle*1.7453293f)+cam.x;
	cam.ly = 2.0;
	cam.lz = (GLfloat)-cos(cam.rotation_angle*1.7453293f)+cam.z;
	cam.moving = MOVE_NONE;
	cam.thr = 10.0;
	sprintf(cam.thr_text, "%d%%", (int)cam.thr);
}

void CameraMove(void) {
	GLfloat mx, mz;
	if (cam.moving & MOVE_FRONT) {
		mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))
			* cam.thr/100.0f * delta_move;
		mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.thr/100.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_BACK) {
		mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))
			* cam.thr/100.0f * delta_move;
		mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.thr/100.0f * delta_move;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_LEFT) {
		mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.thr/160.0f * delta_move;
		mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))
			* cam.thr/160.0f * delta_move;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_RIGHT) {
		mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.thr/160.0f * delta_move;
		mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))
			* cam.thr/160.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_UP) {
		cam.y += 0.01f * cam.thr * delta_move;
		cam.ly += 0.01f * cam.thr * delta_move;
	}
	if (cam.moving & MOVE_DOWN) {
		cam.y -= 0.01f * cam.thr * delta_move;
		cam.ly -= 0.01f * cam.thr * delta_move;
	}
	if (cam.moving & LOOK_LEFT)
		CameraRotateStep(-0.01);
	if (cam.moving & LOOK_RIGHT)
		CameraRotateStep(0.01);
	
	if (cam.moving & THR_DOWN) {
		if (cam.thr > 0.0)
			cam.thr -= delta_move/2;
			sprintf(cam.thr_text, "%d%%", (int)cam.thr);
	}
	if (cam.moving & THR_UP) {
		if (cam.thr < 100.0) {
			cam.thr += delta_move/2;
			sprintf(cam.thr_text, "%d%%", (int)cam.thr);
		}
	}
}

void CameraRotateStep(GLfloat angle) {
	cam.rotation_angle += angle;

	if (angle > 0.0)
		if (cam.rotation_angle >= 3.6) cam.rotation_angle -= 3.6;
	else if (angle < 0.0)
		if (cam.rotation_angle < 0.0) cam.rotation_angle += 3.6;
	
	cam.lx = (GLfloat)sin(cam.rotation_angle*1.7453293f) + cam.x;
	cam.lz = (GLfloat)-cos(cam.rotation_angle*1.7453293f) + cam.z;
}

