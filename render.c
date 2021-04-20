#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, winW/winH, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.x, cam.y, cam.z,
			cam.lx, cam.ly, cam.lz,
			0.0, 1.0, 0.0);

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glEnd();
	glColor3f(0.3, 0.8, 0.3);
	glBegin(GL_LINES);
	GLfloat cnt;
	for (cnt = -50.0; cnt <= 50.0; cnt += 1.0) {
		glVertex3f(cnt, 0.1, 50.0);
		glVertex3f(cnt, 0.1, -50.0);
	}
	for (cnt = 50.0; cnt >= -50.0; cnt -= 1.0) {
		glVertex3f(-50.0, 0.1, cnt);
		glVertex3f(50.0, 0.1, cnt);
	}
	glEnd();

	glPushMatrix();
	glTranslatef(flagX, flagY + 0.5, flagZ);
	glRotatef(delta, 0.0, 1.0, 0.0);
	glColor3f(0.6, 0.7, 0.8);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glEnd();
	glPopMatrix();

	FlagRender();

	SDL_GL_SwapWindow(window);
}
