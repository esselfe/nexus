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
	cam.speed = 0.0;
	sprintf(cam.speed_text, "0");
}

void CameraMove(void) {
	//if (cam.speed > 0.0 && (cam.moving & MOVE_ACCEL) && 
	//  ((cam.moving & MOVE_FRONT) == 0 && (cam.moving & MOVE_BACK) == 0 &&
	//  (cam.moving & MOVE_LEFT) == 0 && (cam.moving & MOVE_RIGHT) == 0 &&
	//  (cam.moving & MOVE_UP) == 0 && (cam.moving & MOVE_DOWN) == 0)) {
	  	
	//}

	if (cam.moving & MOVE_ACCEL) {
		if (cam.speed < cam.thr)
			cam.speed += cam.thr/100.0;
		sprintf(cam.speed_text, "%d", (int)cam.speed);
	}
	else if (cam.moving & MOVE_DECEL) {
		if (cam.speed > 0.0) {
			cam.speed -= 0.01*cam.thr;
			sprintf(cam.speed_text, "%d", (int)cam.speed);
		}
		
		if (cam.speed <= 0.0) {
			cam.speed = 0.0;
			cam.moving ^= MOVE_DECEL;
			if (cam.moving & MOVE_FRONT)
				cam.moving ^= MOVE_FRONT;
			if (cam.moving & MOVE_BACK)
				cam.moving ^= MOVE_BACK;
			if (cam.moving & MOVE_LEFT)
				cam.moving ^= MOVE_LEFT;
			if (cam.moving & MOVE_RIGHT)
				cam.moving ^= MOVE_RIGHT;
			if (cam.moving & MOVE_UP)
				cam.moving ^= MOVE_UP;
			if (cam.moving & MOVE_DOWN)
				cam.moving ^= MOVE_DOWN;
		}
	}

	GLfloat mx, mz;
	if (cam.moving & MOVE_FRONT) {
		mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_BACK) {
		mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_LEFT) {
		mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.speed/160.0f * delta_move;
		mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))
			* cam.speed/160.0f * delta_move;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_RIGHT) {
		mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.speed/160.0f * delta_move;
		mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))
			* cam.speed/160.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_UP) {
		cam.y += 0.01f * cam.speed * delta_move;
		cam.ly += 0.01f * cam.speed * delta_move;
	}
	if (cam.moving & MOVE_DOWN) {
		cam.y -= 0.01f * cam.speed * delta_move;
		cam.ly -= 0.01f * cam.speed * delta_move;
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

