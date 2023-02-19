#include <stdio.h>
#include <GL/gl.h>

#include "nexus.h"

int goto_enabled;
GLfloat goto_x, goto_z, goto_angle, goto_angle_left;

void CameraGoto(GLfloat x, GLfloat z) {
	goto_enabled = 1;
	goto_x = x;
	goto_z = z;
	goto_angle = atan((z-cam.z)/(x-cam.x)) * (180.0/M_PI) / 100.0;
	
	if (x-cam.x > 0.0 && z-cam.z > 0.0)
		goto_angle += 0.9;
	else if (x-cam.x > 0.0 && z-cam.z < 0.0)
		goto_angle += 0.9;
	else if (x-cam.x < 0.0 && z-cam.z < 0.0)
		goto_angle -= 0.9;
	else if (x-cam.x < 0.0 && z-cam.z > 0.0)
		goto_angle -= 0.9;
	
	if (goto_angle < 0.0)
		goto_angle += 3.6;
	
	goto_angle_left = goto_angle - cam.rotation_angle;
	if (goto_angle_left < 0.0)
		goto_angle_left += 3.6;
}

void CameraGotoMove(void) {
	if (goto_angle_left < -0.01) {
		goto_angle_left += 0.01;
		CameraRotateStep(-0.01);
	}
	else if (goto_angle_left > 0.01) {
		goto_angle_left -= 0.01;
		CameraRotateStep(0.01);
	}
	
	if (goto_angle_left <= 0.01 && goto_angle_left > 0.0) {
	  	goto_angle_left = 0.0;
		cam.moving |= MOVE_FRONT;
		cam.moving |= MOVE_ACCEL;
	}
	
	if (cam.moving & MOVE_FRONT) {
		if ((cam.x < goto_x + cam.thr/4 && cam.x > goto_x - cam.thr/4) &&
		  (cam.z < goto_z + cam.thr/4 && cam.z > goto_z - cam.thr/4)) {
			goto_enabled = 0;
			cam.moving |= MOVE_DECEL;
			if (cam.moving & MOVE_ACCEL)
				cam.moving ^= MOVE_ACCEL;
		}
	}
}

