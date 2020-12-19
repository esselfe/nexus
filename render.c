#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, winW, winH, 0.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 10.0,
			0.0, 1.0, 0.0,
			0.0, 1.0, 0.0);

	glTranslatef(winW/2, winH/2, 0.0);
	glRotatef(delta, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.7, 0.8);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	SDL_GL_SwapWindow(window);
}
