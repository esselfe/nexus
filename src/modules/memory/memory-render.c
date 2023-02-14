#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "nexus.h"

GLfloat memory_max, memory_value;
char memory_max_text[128] = "0", memory_value_text[128] = "0";
GLfloat swap_max, swap_value;
char swap_max_text[128] = "0", swap_value_text[128] = "0";

void MemoryRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Switch to 3D rendering (Scene)
	RenderSet3DView();

	SkyRender();
	FloorRender();

	// Render memory meter
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glColor3f(0.2, 0.3, 0.4);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glVertex3f(1.0, 3.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.5, 0.6, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, memory_value, 0.0);
	glVertex3f(1.0, memory_value, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	FontRender(-1.0, 3.32, 0.0, "RAM");
	FontRender(-1.0, 3.16, 0.0, memory_max_text);
	FontRender(-1.0, memory_value, 0.0, memory_value_text);

	// Render swap meter
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glColor3f(0.2, 0.3, 0.4);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glVertex3f(1.0, 3.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.5, 0.6, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, swap_value, 0.0);
	glVertex3f(1.0, swap_value, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
	FontRender(1.0, 3.32, 0.0, "Swap");
	FontRender(1.0, 3.16, 0.0, swap_max_text);
	FontRender(1.0, swap_value, 0.0, swap_value_text);

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

