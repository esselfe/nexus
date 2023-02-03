#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void (*RenderFunc)(void);

void RenderInit(void) {
	RenderFunc = Render;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport((GLint)0, (GLint)0, (GLsizei)winW, (GLsizei)winH);
}

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
	RenderThrottle();
	
	/*char *c = malloc(2);
	memset(c, 0, 2);
	int i;
	for (i = 32; i < 126; i++) {
		*c = (char)i;
		FontRender2D((i-32)*8, 40, c);
	}
	*c = (char)'!';
	FontRender2D(10, 58, c);
	*c = (char)' ';
	FontRender2D(10, 74, c); */

	SDL_GL_SwapWindow(window);
}

void RenderCursor(void) {
	glPushMatrix();
	glTranslatef((GLfloat)mouse_x, winH - (GLfloat)mouse_y, 0.0);
	glBegin(GL_LINES);
	glColor3f(0.7, 0.8, 0.9);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 10.0);
	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	glEnd();
	glPopMatrix();
}

void RenderThrottle(void) {
	glPushMatrix();
	glTranslatef(winW-20.0, winH/2, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.7, 0.8);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, cam.thr);
	glVertex2f(0.0, cam.thr);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.3, 0.4, 0.5);
	glVertex2f(-1.0, -1.0);
	glVertex2f(11.0, -1.0);
	glVertex2f(11.0, 101.0);
	glVertex2f(-1.0, 101.0);
	glVertex2f(-1.0, -1.0);
	glEnd();
	glPopMatrix();
	FontRender2D(winW-strlen(cam.thr_text)*8, winH/2-20, cam.thr_text);
}

void RenderFloor(void) {
	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.1, 0.1, 1.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glEnd();
	
	glBegin(GL_LINES);
	glColor4f(0.15, 0.15, 0.15, 0.25);
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

