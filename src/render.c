#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"

void (*RenderFunc)(void);

GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 100.0, 1.0, 0.0 };

void RenderInit(void) {
	if (verbose) printf("Initializing rendering\n");
	
	RenderFunc = Render;
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport((GLint)0, (GLint)0, (GLsizei)winW, (GLsizei)winH);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void RenderSet3DView(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, winW/winH, 0.01, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.x, cam.y, cam.z,
			cam.lx, cam.ly, cam.lz,
			0.0, 1.0, 0.0);
}

void RenderSet2DView(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, winW, 0.0, winH, 0.0, 10.0);
	gluOrtho2D(0.0, winW, 0.0, winH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	RenderSet3DView();

	SkyRender();
	FloorRender();
	FlagRender();

	// Switch to 2D rendering (HUD)
	RenderSet2DView();

	FontRender2D(10, (int)winH-16-10, fps_text);
	if (terminal_visible)
		TerminalRender();
	if (!mouse_held)
		RenderCursor();
	RenderThrottle();

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
	FontRender2D(winW-strlen(cam.speed_text)*8, winH/2-40, cam.speed_text);
}

