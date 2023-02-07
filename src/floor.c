#include <GL/gl.h>

void FloorInit(void) {
	return;
}

void FloorRender(void) {
	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.1, 0.1, 1.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glEnd();
	
	glBegin(GL_LINES);
	glColor4f(0.15, 0.15, 0.15, 0.4);
	GLfloat cnt;
	for (cnt = -50.0; cnt <= 50.0; cnt += 1.0) {
		glVertex3f(cnt, 0.02, 50.0);
		glVertex3f(cnt, 0.02, -50.0);
	}
	for (cnt = 50.0; cnt >= -50.0; cnt -= 1.0) {
		glVertex3f(-50.0, 0.02, cnt);
		glVertex3f(50.0, 0.02, cnt);
	}
	glEnd();
}

