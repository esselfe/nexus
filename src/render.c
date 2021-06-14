#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void (*RenderFunc)(void);

void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, winW/winH, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.x, cam.y, cam.z,
			cam.lx, cam.ly, cam.lz,
			0.0, 1.0, 0.0);

	SkyRender();
	RenderFloor();
	FlagRender();

	// Switch to 2D rendering (HUD)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, winW, 0.0, winH, 0.0, 10.0);
	gluOrtho2D(0.0, winW, 0.0, winH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	FontRender2D(10, (int)winH-16-10, fps_text);
	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		RenderCursor();

	SDL_GL_SwapWindow(window);
}

void RenderCursor(void) {
	glColor3f(0.7, 0.8, 0.9);
	glPushMatrix();
	glTranslatef((GLfloat)mouse_x, winH - (GLfloat)mouse_y, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 10.0);
	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	glEnd();
	glPopMatrix();
}

void RenderFloor(void) {
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glEnd();
	glColor3f(0.15, 0.15, 0.15);
	glBegin(GL_LINES);
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

