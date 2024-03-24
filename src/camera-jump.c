#include <math.h>
#include <GL/gl.h>

#include "nexus.h"
#include "camera.h"

// Should be called from the terminal, immediately change the camera position
void CameraJump(GLfloat x, GLfloat z) {
	cam.x = x;
	cam.lx = x + sin(cam.rotation_angle * (M_PI/180.0));
	cam.z = z;
	cam.lz = z + cos(cam.rotation_angle * (M_PI/180.0));
}

