#include <math.h>
#include <GL/gl.h>

#include "nexus.h"

void CameraRotateStep(GLfloat angle) {
	cam.rotation_angle += angle;
	printf("cam angle: %f\n", cam.rotation_angle);

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

