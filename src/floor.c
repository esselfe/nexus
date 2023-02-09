#include <GL/gl.h>

unsigned int floor_factor;

void FloorInit(void) {
	if (floor_factor == 0)
		floor_factor = 4;
}

void FloorRender(void) {
	GLfloat floor_size = 50.0 * floor_factor;

	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.1, 0.1, 1.0);
	glVertex3f(-floor_size, 0.0, floor_size);
	glVertex3f(floor_size, 0.0, floor_size);
	glVertex3f(floor_size, 0.0, -floor_size);
	glVertex3f(-floor_size, 0.0, -floor_size);
	glVertex3f(-floor_size, 0.0, floor_size);
	glEnd();
	
	glBegin(GL_LINES);
	glColor4f(0.15, 0.15, 0.15, 0.4);
	GLfloat cnt;
	for (cnt = -floor_size; cnt <= floor_size; cnt += 1.0) {
		glVertex3f(cnt, 0.02, floor_size);
		glVertex3f(cnt, 0.02, -floor_size);
	}
	for (cnt = floor_size; cnt >= -floor_size; cnt -= 1.0) {
		glVertex3f(-floor_size, 0.02, cnt);
		glVertex3f(floor_size, 0.02, cnt);
	}
	glEnd();
}

