#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "nexus.h"
#include "camera.h"
#include "event.h"
#include "flag.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "image.h"
#include "render.h"
#include "sky.h"
#include "terminal.h"
#include "window.h"

void (*RenderFunc)(void);

unsigned int fps; // For measuring frames per second
char *fps_text; // Text rendered on the HUD
GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 20.0, 1.0, 0.0 };

void RenderInit(void) {
	if (verbose) printf("Initializing rendering\n");
	
	fps_text = malloc(20);
	sprintf(fps_text, "0 fps");
	
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
	glScalef(-1.0, 1.0, 1.0);
	gluPerspective(60.0, winW/winH, 0.01, 1500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.x, cam.y, cam.z,
			cam.lx, cam.ly, cam.lz,
			0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, -1.0);
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

	HudRender();

	SDL_GL_SwapWindow(window);
}

