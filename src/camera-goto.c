#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include "nexus.h"
#include "camera.h"

// Automation flags and variables
int goto_enabled, goto_stopping;
GLfloat goto_x, goto_z, goto_angle, goto_angle_left;

// This should be called from the terminal
void CameraGoto(GLfloat x, GLfloat z) {
	goto_enabled = 1;
	goto_x = x;
	goto_z = z;
	GLfloat denom = x-cam.x;
	// Prevent division by zero errors
	if (denom == 0.0)
		goto_angle = -atan((z-cam.z)/0.0000001) * (180.0/M_PI);
	else
		goto_angle = -atan((z-cam.z)/denom) * (180.0/M_PI);
	
	if ((x-cam.x >= 0.0 && z-cam.z >= 0.0) || 
	  (x-cam.x >= 0.0 && z-cam.z <= 0.0))
		goto_angle += 90.0;
	else if ((x-cam.x <= 0.0 && z-cam.z <= 0.0) ||
	  (x-cam.x <= 0.0 && z-cam.z >= 0.0))
		goto_angle -= 90.0;
	
	if (goto_angle < 0.0)
		goto_angle += 360.0;
	
	goto_angle_left = goto_angle - cam.rotation_angle;
	if (goto_angle_left < 0.0)
		goto_angle_left += 360.0;
}

void CameraGotoMove(void) {
	if (goto_angle_left >= 1.0) {
		goto_angle_left -= 1.0;
		CameraRotateStep(1.0);
	}
	
	if (goto_angle_left <= 1.0) {
	  	goto_angle_left = 0.0;
		cam.moving |= MOVE_FRONT;
		cam.moving |= MOVE_ACCEL;
	}
	
	if (cam.moving & MOVE_FRONT) {
		if ((cam.x < goto_x + cam.speed/3.4 && cam.x > goto_x - cam.speed/3.4) &&
		  (cam.z < goto_z + cam.speed/3.4 && cam.z > goto_z - cam.speed/3.4)) {
			goto_enabled = 0;
			goto_stopping = 1;
			cam.moving |= MOVE_DECEL;
			if (cam.moving & MOVE_ACCEL)
				cam.moving ^= MOVE_ACCEL;
		}
	}
}

