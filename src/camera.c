#include <math.h>
#include <GL/gl.h>

#include "nexus.h"

struct Camera cam;

void CameraMove(void) {
	GLfloat mx, mz;
    if (cam.moving & MOVE_FRONT) {
        mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/100.0f;
        mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/100.0f;
        cam.x += mx;
        cam.lx += mx;
        cam.z -= mz;
        cam.lz -= mz;
    }
	if (cam.moving & MOVE_BACK) {
        mx = (GLfloat)(sin(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/100.0f;
        mz = (GLfloat)(cos(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/100.0f;
        cam.x -= mx;
        cam.lx -= mx;
        cam.z += mz;
        cam.lz += mz;
    }
	if (cam.moving & MOVE_LEFT) {
        mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/160.0f;
        mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))        * (GLfloat)cam.thr/160.0f;
        cam.x -= mx;
        cam.lx -= mx;
        cam.z += mz;
        cam.lz += mz;
    }
    if (cam.moving & MOVE_RIGHT) {
        mx = (GLfloat)(cos(cam.rotation_angle*1.7453293f))         * (GLfloat)cam.thr/160.0f;
        mz = (GLfloat)(-sin(cam.rotation_angle*1.7453293f))        * (GLfloat)cam.thr/160.0f;
        cam.x += mx;
        cam.lx += mx;
        cam.z -= mz;
        cam.lz -= mz;
    }
    if (cam.moving & MOVE_UP) {
        cam.y += 0.01f * (GLfloat)cam.thr;
        cam.ly += 0.01f * (GLfloat)cam.thr;
    }
    if (cam.moving & MOVE_DOWN) {
        cam.y -= 0.01f * (GLfloat)cam.thr;
        cam.ly -= 0.01f * (GLfloat)cam.thr;
    }
}

void CameraRotateStep(GLfloat angle) {
	cam.rotation_angle += angle;

	if (angle > 0.0) {
        if (cam.rotation_angle >= 3.6) cam.rotation_angle -= 3.6;
        cam.lx = (GLfloat)sin(cam.rotation_angle*1.7453293f)+cam.x;
        cam.lz = (GLfloat)-cos(cam.rotation_angle*1.7453293f)+cam.z;
    }
    else if (angle < 0.0) {
        if (cam.rotation_angle < 0.0) cam.rotation_angle += 3.6;
        cam.lx = (GLfloat)sin(cam.rotation_angle*1.7453293f)+cam.x;
        cam.lz = (GLfloat)-cos(cam.rotation_angle*1.7453293f)+cam.z;
	}
}

