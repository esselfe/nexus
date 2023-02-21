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
	cam.rotation_angle = 0.0;
	cam.lx = cam.x + (GLfloat)sin(cam.rotation_angle*1.7453293f);
	cam.ly = 2.0;
	cam.lz = cam.z + (GLfloat)-cos(cam.rotation_angle*1.7453293f);
	cam.moving = MOVE_NONE;
	cam.thr = 10.0;
	sprintf(cam.thr_text, "%d%%", (int)cam.thr);
	cam.speed = 0.0;
	sprintf(cam.speed_text, "0");
	cam.side_speed = 0.0;
	sprintf(cam.side_speed_text, "0");
	cam.height_speed = 0.0;
	sprintf(cam.height_speed_text, "0");
}

void CameraMove(void) {
	if (cam.moving & MOVE_ACCEL) {
		if (cam.moving & MOVE_FRONT) {
			if (cam.speed < cam.thr)
				cam.speed += cam.thr/100.0;
			if (cam.speed >= cam.thr) {
				cam.speed = cam.thr;
				cam.moving ^= MOVE_ACCEL;
			}
		}
		if (cam.moving & MOVE_BACK) {
			if (cam.speed > -cam.thr)
				cam.speed -= cam.thr/100.0;
			if (cam.speed <= -cam.thr) {
				cam.speed = -cam.thr;
				cam.moving ^= MOVE_ACCEL;
			}
		}
		sprintf(cam.speed_text, "%d", (int)cam.speed);
	}
	if (cam.moving & MOVE_DECEL) {
		if (cam.moving & MOVE_FRONT) {
			if (cam.speed > 0.0)
				cam.speed -= 0.01*cam.thr;
			if (cam.speed <= 0.0) {
				cam.speed = 0.0;
				cam.moving ^= MOVE_DECEL;
				if (cam.moving & MOVE_FRONT)
					cam.moving ^= MOVE_FRONT;
				if (cam.moving & MOVE_BACK)
					cam.moving ^= MOVE_BACK;
				if (cam.moving & MOVE_UP)
					cam.moving ^= MOVE_UP;
				if (cam.moving & MOVE_DOWN)
					cam.moving ^= MOVE_DOWN;
			}
		}
		if (cam.moving & MOVE_BACK) {
			if (cam.speed < 0.0)
				cam.speed += 0.01*cam.thr;
			if (cam.speed >= 0.0) {
				cam.speed = 0.0;
				cam.moving ^= MOVE_DECEL;
				if (cam.moving & MOVE_FRONT)
					cam.moving ^= MOVE_FRONT;
				if (cam.moving & MOVE_BACK)
					cam.moving ^= MOVE_BACK;
				if (cam.moving & MOVE_UP)
					cam.moving ^= MOVE_UP;
				if (cam.moving & MOVE_DOWN)
					cam.moving ^= MOVE_DOWN;
			}
		}
		sprintf(cam.speed_text, "%d", (int)cam.speed);
	}
	
	if (cam.moving & MOVE_SIDE_ACCEL) {
		if (cam.moving & MOVE_RIGHT) {
			if (cam.side_speed < cam.thr)
				cam.side_speed += cam.thr/100.0;
			if (cam.side_speed >= cam.thr) {
				cam.side_speed = cam.thr;
				cam.moving ^= MOVE_SIDE_ACCEL;
			}
		}
		if (cam.moving & MOVE_LEFT) {
			if (cam.side_speed > -cam.thr)
				cam.side_speed -= cam.thr/100.0;
			if (cam.side_speed <= -cam.thr) {
				cam.side_speed = -cam.thr;
				cam.moving ^= MOVE_SIDE_ACCEL;
			}
		}
		sprintf(cam.side_speed_text, "%d", (int)cam.side_speed);
	}
	else if (cam.moving & MOVE_SIDE_DECEL) {
		if (cam.moving & MOVE_RIGHT) {
			if (cam.side_speed > 0.0)
				cam.side_speed -= 0.01*cam.thr;
			if (cam.side_speed <= 0.0) {
				cam.side_speed = 0.0;
				cam.moving ^= MOVE_SIDE_DECEL;
				if (cam.moving & MOVE_LEFT)
					cam.moving ^= MOVE_LEFT;
				if (cam.moving & MOVE_RIGHT)
					cam.moving ^= MOVE_RIGHT;
			}
		}
		if (cam.moving & MOVE_LEFT) {
			if (cam.side_speed < 0.0)
				cam.side_speed += 0.01*cam.thr;
			if (cam.side_speed >= 0.0) {
				cam.side_speed = 0.0;
				cam.moving ^= MOVE_SIDE_DECEL;
				if (cam.moving & MOVE_LEFT)
					cam.moving ^= MOVE_LEFT;
				if (cam.moving & MOVE_RIGHT)
					cam.moving ^= MOVE_RIGHT;
			}
		}
		sprintf(cam.side_speed_text, "%d", (int)cam.side_speed);
	}
	
	if (cam.moving & MOVE_HEIGHT_ACCEL) {
		if (cam.moving & MOVE_UP) {
			if (cam.height_speed < cam.thr)
				cam.height_speed += cam.thr/100.0;
			if (cam.height_speed >= cam.thr) {
				cam.height_speed = cam.thr;
				cam.moving ^= MOVE_HEIGHT_ACCEL;
			}
		}
		if (cam.moving & MOVE_DOWN) {
			if (cam.height_speed > -cam.thr)
				if (cam.y > 0.01) cam.height_speed -= cam.thr/100.0;
			if (cam.height_speed <= -cam.thr) {
				cam.height_speed = -cam.thr;
				cam.moving ^= MOVE_HEIGHT_ACCEL;
			}
		}
		sprintf(cam.height_speed_text, "%d", (int)cam.height_speed);
	}
	else if (cam.moving & MOVE_HEIGHT_DECEL) {
		if (cam.moving & MOVE_UP) {
			if (cam.height_speed > 0.0)
				cam.height_speed -= 0.01*cam.thr;
			if (cam.height_speed <= 0.0) {
				cam.height_speed = 0.0;
				cam.moving ^= MOVE_HEIGHT_DECEL;
			}
		}
		if (cam.moving & MOVE_DOWN) {
			if (cam.height_speed < 0.0)
				cam.height_speed += 0.01*cam.thr;
			if (cam.height_speed >= 0.0) {
				cam.height_speed = 0.0;
				cam.moving ^= MOVE_HEIGHT_DECEL;
			}
		}
		sprintf(cam.height_speed_text, "%d", (int)cam.height_speed);
	}

	GLfloat mx, mz;
	if (cam.moving & MOVE_FRONT || cam.moving & MOVE_BACK) {
		mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.speed/100.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_LEFT || cam.moving & MOVE_RIGHT) {
		mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))
			* cam.side_speed/160.0f * delta_move;
		mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))
			* cam.side_speed/160.0f * delta_move;
		cam.x += mx;
		cam.lx += mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	
	if (cam.moving & MOVE_UP) {
		cam.y += 0.01 * cam.height_speed * delta_move;
		cam.ly += 0.01 * cam.height_speed * delta_move;
	}
	if (cam.moving & MOVE_DOWN) {
		if (cam.y > 0.01) {
			cam.y += 0.01 * cam.height_speed * delta_move;
			cam.ly += 0.01 * cam.height_speed * delta_move;
		}
	}
	if (cam.y < 0.01) {
		cam.y = 0.01;
		cam.ly = 0.01;
		cam.height_speed = 0.0;
		sprintf(cam.height_speed_text, "0");
		if (cam.moving & MOVE_DOWN)
			cam.moving ^= MOVE_DOWN;
		if (cam.moving & MOVE_HEIGHT_DECEL)
			cam.moving ^= MOVE_HEIGHT_DECEL;
		if (cam.moving & MOVE_HEIGHT_ACCEL)
			cam.moving ^= MOVE_HEIGHT_ACCEL;
	}
	
	if (!goto_enabled) {
		if (cam.moving & LOOK_LEFT)
			CameraRotateStep(-0.01);
		if (cam.moving & LOOK_RIGHT)
			CameraRotateStep(0.01);
	}
	
	if (cam.moving & THR_DOWN) {
		if (cam.thr > 0.0) {
			cam.thr -= delta_move/2.0;
			sprintf(cam.thr_text, "%d%%", (int)cam.thr);
			cam.moving |= MOVE_DECEL;
			cam.moving |= MOVE_SIDE_DECEL;
		}
	}
	if (cam.moving & THR_UP) {
		if (cam.thr < 100.0) {
			cam.thr += delta_move/2.0;
			sprintf(cam.thr_text, "%d%%", (int)cam.thr);
			cam.moving |= MOVE_ACCEL;
			cam.moving |= MOVE_SIDE_ACCEL;
		}
	}
}

void CameraRotateStep(GLfloat angle) {
	cam.rotation_angle += angle;

	if (cam.rotation_angle >= 3.6) cam.rotation_angle -= 3.6;
	if (cam.rotation_angle < 0.0) cam.rotation_angle += 3.6;
	
	cam.lx = cam.x + (GLfloat)sin(cam.rotation_angle*1.7453293f);
	cam.lz = cam.z + (GLfloat)-cos(cam.rotation_angle*1.7453293f);
}

void CameraStop(void) {
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
	if (cam.moving & MOVE_ACCEL)
		cam.moving ^= MOVE_ACCEL;
	if (cam.moving & MOVE_DECEL)
		cam.moving ^= MOVE_DECEL;
	if (cam.moving & MOVE_SIDE_ACCEL)
		cam.moving ^= MOVE_SIDE_ACCEL;
	if (cam.moving & MOVE_SIDE_DECEL)
		cam.moving ^= MOVE_SIDE_DECEL;
	if (cam.moving & MOVE_HEIGHT_ACCEL)
		cam.moving ^= MOVE_HEIGHT_ACCEL;
	if (cam.moving & MOVE_HEIGHT_DECEL)
		cam.moving ^= MOVE_HEIGHT_DECEL;
	cam.speed = 0.0;
	sprintf(cam.speed_text, "0");
	cam.side_speed = 0.0;
	sprintf(cam.side_speed_text, "0");
	cam.height_speed = 0.0;
	sprintf(cam.height_speed_text, "0");
	goto_enabled = 0;
}

